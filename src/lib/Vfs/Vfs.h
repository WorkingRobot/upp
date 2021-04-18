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

        std::unique_ptr<Objects::FArchive> GetFile(const char* Path);

        std::unique_ptr<Objects::FArchive> GetFile(const File& File);

    private:
        Directory<> Root;
        std::vector<std::unique_ptr<Readers::BaseReader>> Readers;
        uint32_t NextReaderIdx;
    };
}