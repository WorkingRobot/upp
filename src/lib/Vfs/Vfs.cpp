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

    const std::unique_ptr<Providers::BaseProvider>& Vfs::GetProvider() const
    {
        return Provider;
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

    bool Vfs::FindChunk(const Objects::FIoChunkId& Id, File& File)
    {
        for (auto& Reader : Readers) {
            auto Idx = Reader->FindChunk(Id);
            if (Idx != -1) {
                File = upp::Vfs::File(Reader->GetReaderIdx(), Idx);
                return true;
            }
        }
        return false;
    }

    std::unique_ptr<Objects::FArchive> Vfs::GetFile(const char* Path)
    {
        if (*Path == '/') {
            Path++;
        }

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

    std::unique_ptr<Objects::UPackage> Vfs::GetPackage(const char* Path)
    {
        if (*Path == '/') {
            Path++;
        }

        auto AssetFile = Root.TryGetFile((std::string(Path) + ".uasset").c_str());
        if (!AssetFile) {
            AssetFile = Root.TryGetFile((std::string(Path) + ".umap").c_str());
            if (!AssetFile) {
                return nullptr;
            }
        }

        return GetPackage(*AssetFile);
    }

    std::unique_ptr<Objects::UPackage> Vfs::GetPackage(const File& File)
    {
        auto ReaderItr = std::find_if(Readers.begin(), Readers.end(),
            [ReaderIdx = File.GetReaderIdx()](const std::unique_ptr<Readers::BaseReader>& Ptr) {
                return Ptr->GetReaderIdx() == ReaderIdx;
            }
        );
        if (ReaderItr == Readers.end()) {
            return nullptr;
        }

        return (*ReaderItr)->ExportPackage(File.GetFileIdx(), *this);
    }

    std::unique_ptr<Objects::UPackage> Vfs::GetPackageMinimal(const char* Path)
    {
        if (*Path == '/') {
            Path++;
        }

        auto AssetFile = Root.TryGetFile((std::string(Path) + ".uasset").c_str());
        if (!AssetFile) {
            AssetFile = Root.TryGetFile((std::string(Path) + ".umap").c_str());
            if (!AssetFile) {
                return nullptr;
            }
        }

        return GetPackageMinimal(*AssetFile);
    }

    std::unique_ptr<Objects::UPackage> Vfs::GetPackageMinimal(const File& File)
    {
        auto ReaderItr = std::find_if(Readers.begin(), Readers.end(),
            [ReaderIdx = File.GetReaderIdx()](const std::unique_ptr<Readers::BaseReader>& Ptr) {
            return Ptr->GetReaderIdx() == ReaderIdx;
        }
        );
        if (ReaderItr == Readers.end()) {
            return nullptr;
        }

        return (*ReaderItr)->ExportPackageMinimal(File.GetFileIdx(), *this);
    }
}