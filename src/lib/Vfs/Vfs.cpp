#include "Vfs.h"

namespace upp::Vfs {
    Vfs::Vfs() :
        NextReaderIdx(0)
    {

    }

    const GlobalData& Vfs::GetGlobalData() const
    {
        return Global;
    }

    GlobalData& Vfs::GetGlobalData()
    {
        return Global;
    }

    const Directory<>& Vfs::GetRootDirectory() const
    {
        return Root;
    }

    Directory<>& Vfs::GetRootDirectory()
    {
        return Root;
    }

    bool Vfs::RemoveReader(uint32_t ReaderIdx)
    {
        auto Itr = std::find_if(Readers.begin(), Readers.end(),
            [ReaderIdx](const std::unique_ptr<Readers::BaseReader>& Ptr) {
                return Ptr->GetReaderIdx() == ReaderIdx;
            }
        );
        if (Itr == Readers.end()) {
            return false;
        }

        Readers.erase(Itr);

        return true;
    }

    std::unique_ptr<Objects::FArchive> Vfs::GetFile(const char* Path)
    {
        auto File = Root.TryGetFile(Path);
        if (!File) {
            return nullptr;
        }
        
        return GetFile(*File);
    }

    std::unique_ptr<Objects::FArchive> Vfs::GetFile(const File& File)
    {
        auto ReaderItr = std::find_if(Readers.begin(), Readers.end(),
            [ReaderIdx = File.GetReaderIdx()](const std::unique_ptr<Readers::BaseReader>& Ptr) {
                return Ptr->GetReaderIdx() == ReaderIdx;
            }
        );
        if (ReaderItr == Readers.end()) {
            return nullptr;
        }

        return (*ReaderItr)->OpenFile(File.GetFileIdx());
    }
}