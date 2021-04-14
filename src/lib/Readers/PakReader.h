#pragma once

#include "../Objects/PakFile/FPakInfo.h"
#include "../Objects/PakFile/FPakEntry.h"
#include "BaseReader.h"

#include <variant>

namespace upp::Readers {
    class PakReader : public BaseReader {
    public:
        PakReader(Objects::FArchive& Archive, const IKeyChain& KeyChain, uint32_t ReaderIdx = -1);

        void Append(Vfs::BaseVfs& Vfs) override;

    private:
        std::unique_ptr<char[]> GetIndexArchive(int64_t Offset, int64_t Size, const Objects::FSHAHash& Hash);

        void ReadIndex();

        void ReadIndexLegacy();

        Objects::FPakInfo Info;

    public:
        Vfs::Directory<> Index;

        std::variant<std::vector<Objects::FPakEntry>, std::unique_ptr<char[]>> EntryData;
    };
}