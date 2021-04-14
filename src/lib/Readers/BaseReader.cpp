#include "BaseReader.h"

#include <atomic>

namespace upp::Readers {
    BaseReader::BaseReader(Objects::FArchive& Archive, const IKeyChain& KeyChain, uint32_t ReaderIdx) :
        Ar(Archive),
        KeyChain(KeyChain),
        ReaderIdx(ReaderIdx == -1 ? GenerateReaderIdx() : ReaderIdx),
        StoredError(Error::None)
    {

    }

    bool BaseReader::HasError() const
    {
        return StoredError == Error::None;
    }

    Error BaseReader::GetError() const
    {
        return StoredError;
    }

    uint32_t BaseReader::GetReaderIdx() const
    {
        return ReaderIdx;
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

    void BaseReader::CompactFilePath(std::string& Path)
    {
        if (Path[0] != '/') {
            return;
        }
        else if (Path.starts_with("/Engine/Content")) { // -> /Engine
            Path.erase(7, 8);
        }
        else if (Path.starts_with("/Engine/Plugins")) { // -> /Plugins
            Path.erase(0, 7);
        }
        else {
            auto SepPos = Path.find('/', 1);
            if (SepPos == std::string::npos)
                return;
            if (Path.compare(SepPos, 9, "/Content/") != 0)
                return;

            if (SepPos > 4) {
                // /FortniteGame/Content -> /Game
                Path.replace(1, SepPos + 7, "Game");
            }
        }
    }

    uint32_t BaseReader::GenerateReaderIdx()
    {
        static std::atomic<uint32_t> Idx(0);
        return ++Idx;
    }
}