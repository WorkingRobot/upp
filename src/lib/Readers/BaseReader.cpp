#include "BaseReader.h"

#include "../Vfs/DirectoryIterator.h"
#include "../Vfs/Vfs.h"

namespace upp::Readers {
    BaseReader::BaseReader(Objects::FArchive& Archive, const IKeyChain& KeyChain, uint32_t ReaderIdx) :
        Ar(Archive),
        KeyChain(KeyChain),
        StoredError(Error::None),
        ReaderIdx(ReaderIdx)
    {

    }

    bool BaseReader::HasError() const
    {
        return StoredError != Error::None;
    }

    Error BaseReader::GetError() const
    {
        return StoredError;
    }

    uint32_t BaseReader::GetReaderIdx() const
    {
        return ReaderIdx;
    }

    const Objects::FArchive& BaseReader::GetArchive() const
    {
        return Ar;
    }

    void BaseReader::SetError(Error NewError)
    {
        StoredError = NewError;
    }

    // https://github.com/gildor2/UEViewer/blob/eaba2837228f9fe39134616d7bff734acd314ffb/Unreal/FileSystem/FileSystemUtils.cpp

    bool BaseReader::ValidateMountPoint(std::string& MountPoint)
    {
        // Mount point must start with ../../..
        // This negates the path the exe is in (FortniteGame/Binaries/Win64)
        if (!MountPoint.starts_with("../../..")) {
            MountPoint = "/";
            return false;
        }
        MountPoint.erase(0, 8);

        // Mount point must begin with / and no longer be relative (no .)
        if (MountPoint[0] != '/' || ((MountPoint.size() > 1) && (MountPoint[1] == '.'))) {
            MountPoint = "/";
            return false;
        }

        return true;
    }

    void BaseReader::MergeDirectory(Vfs::Vfs& Vfs, bool TranslatePaths, Vfs::Directory<>&& Directory)
    {
        auto& Root = Vfs.GetRootDirectory();

        // "/Engine/Content" is redirected to /Engine
        // "/Engine/Plugins" is redirected to /Plugins
        // "/..../Content" is redirected to /Game
        if (TranslatePaths){
            Directory.Directories.erase_if([&Root](decltype(*Directory.Directories.begin())& Dir) {
                if (Dir.first == "Engine") {
                    Dir.second.Directories.erase_if([&Root](auto& EngineDir) {
                        if (EngineDir.first == "Content") {
                            auto& TargetDir = Root.CreateDirectory<true>("Engine", 6);
                            TargetDir.MergeDirectory<true>(std::move(EngineDir.second));
                            return true;
                        }
                        else if (EngineDir.first == "Plugins") {
                            auto& TargetDir = Root.CreateDirectory<true>("Plugins", 7);
                            TargetDir.MergeDirectory<true>(std::move(EngineDir.second));
                            return true;
                        }
                        return false;
                    });
                }
                else if (Dir.first.GetSize() >= 4) {
                    Dir.second.Directories.erase_if([&Root](auto& GameDir) {
                        if (GameDir.first == "Content") {
                            auto& TargetDir = Root.CreateDirectory<true>("Game", 4);
                            TargetDir.MergeDirectory<true>(std::move(GameDir.second));
                            return true;
                        }
                        return false;
                    });
                }

                return Dir.second.Directories.size() == 0 && Dir.second.Files.size() == 0;
            });
        }

        Root.MergeDirectory<true>(std::move(Directory));
    }
}