#pragma once

#include "../Readers/BaseReader.h"
#include "Directory.h"

namespace upp::Vfs {
    class Vfs {
    public:
        Vfs();

        //const GlobalData& GetGlobalData() const;

        //GlobalData& GetGlobalData();

        const Directory<>& GetRootDirectory() const;

        Directory<>& GetRootDirectory();

        template<typename T, std::enable_if_t<std::is_base_of_v<Readers::BaseReader, T>, bool> = true>
        T& AddReader(Objects::FArchive& Archive, const IKeyChain& KeyChain) {
            auto& Ret = Readers.emplace_back(std::make_unique<T>(Archive, KeyChain, NextReaderIdx++));
            if (!Ret->HasError()) {
                Ret->Append(*this);
            }
            return *(T*)Ret.get();
        }

        template<typename T, std::enable_if_t<std::is_base_of_v<Readers::BaseReader, T>, bool> = true>
        T* AddReaderIfValid(Objects::FArchive& Archive, const IKeyChain& KeyChain, Readers::Error& Error) {
            auto& Ret = Readers.emplace_back(std::make_unique<T>(Archive, KeyChain, NextReaderIdx++));
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

        std::unique_ptr<Objects::FArchive> GetFile(const char* Path);

        std::unique_ptr<Objects::FArchive> GetFile(const File& File);

    private:
        Directory<> Root;
        std::vector<std::unique_ptr<Readers::BaseReader>> Readers;
        uint32_t NextReaderIdx;
    };
}