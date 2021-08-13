#pragma once

#include "../Objects/Core/IO/FIoChunkId.h"
#include "../Objects/CoreUObject/UObject/UPackage.h"
#include "../Providers/BaseProvider.h"
#include "../Readers/BaseReader.h"
#include "Directory.h"
#include "GlobalData.h"

#include <memory>

namespace upp::Vfs {
    class Vfs {
    public:
        Vfs();

        const GlobalData& GetGlobalData() const;

        GlobalData& GetGlobalData();

        const Directory<>& GetRootDirectory() const;

        Directory<>& GetRootDirectory();

        const std::unique_ptr<Providers::BaseProvider>& GetProvider() const;

        template<typename T, typename... Ts, std::enable_if_t<std::is_base_of_v<Providers::BaseProvider, T>, bool> = true>
        T& SetProvider(Ts&&... Args) {
            Provider = std::make_unique<T>(std::forward<Ts>(Args)...);
            return *(T*)Provider.get();
        }

        template<typename T, typename... Ts, std::enable_if_t<std::is_base_of_v<Readers::BaseReader, T>, bool> = true>
        T& AddReader(Ts&&... Args) {
            auto& Ret = Readers.emplace_back(std::make_unique<T>(std::forward<Ts>(Args)..., NextReaderIdx++));
            if (!Ret->HasError()) {
                Ret->Append(*this);
            }
            return *(T*)Ret.get();
        }

        template<typename T, typename... Ts, std::enable_if_t<std::is_base_of_v<Readers::BaseReader, T>, bool> = true>
        T* AddReaderIfValid(Readers::Error& Error, Ts&&... Args) {
            auto& Ret = Readers.emplace_back(std::make_unique<T>(std::forward<Ts>(Args)..., NextReaderIdx++));
            Error = Ret->GetError();
            if (Ret->HasError()) {
                Readers.pop_back();
                return nullptr;
            }
            Ret->Append(*this);
            return (T*)Ret.get();
        }

        template<typename T, std::enable_if_t<std::is_base_of_v<Readers::BaseReader, T>, bool> = true>
        bool RemoveReader(T& Reader) {
            return RemoveReader(Reader.GetReaderIdx());
        }

        bool RemoveReader(uint32_t ReaderIdx);

        bool FindChunk(const Objects::FIoChunkId& Id, File& File);

        std::unique_ptr<Objects::FArchive> GetFile(const char* Path);

        std::unique_ptr<Objects::FArchive> GetFile(const File& File);

        std::unique_ptr<Objects::UPackage> GetPackage(const char* Path);

        std::unique_ptr<Objects::UPackage> GetPackage(const File& File);

        std::unique_ptr<Objects::UPackage> GetPackageMinimal(const char* Path);

        std::unique_ptr<Objects::UPackage> GetPackageMinimal(const File& File);

        template<class T>
        std::unique_ptr<T> GetAsset(const char* Path)
        {
            if (*Path == '/') {
                Path++;
            }

            auto File = Root.TryGetFile(Path);
            if (!File) {
                return nullptr;
            }

            return GetAsset<T>(*File);
        }

        template<class T>
        std::unique_ptr<T> GetAsset(const File& File)
        {
            auto Ar = GetFile(File);
            if (!Ar) {
                return nullptr;
            }

            return std::make_unique<T>(*Ar);
        }

    private:
        Directory<> Root;
        GlobalData Global;
        std::unique_ptr<Providers::BaseProvider> Provider;

        std::vector<std::unique_ptr<Readers::BaseReader>> Readers;
        uint32_t NextReaderIdx;
    };
}