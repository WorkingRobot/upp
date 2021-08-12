#pragma once

#include "../Objects/PakFile/FPakInfo.h"
#include "../Objects/PakFile/FPakEntry.h"
#include "../Vfs/Directory.h"
#include "../Compression.h"
#include "BaseReader.h"

#include <variant>

namespace upp::Objects {
    class FPakArchiveReaderBase;
}

namespace upp::Readers {
    class PakReader : public BaseReader {
    public:
        PakReader(Objects::FArchive& Archive, const IKeyChain& KeyChain, uint32_t ReaderIdx = -1);

        const Objects::FPakInfo& GetPakInfo() const;

        CompressionMethod GetCompressionMethod(uint32_t CompressionMethodIdx) const;

        std::unique_ptr<Objects::FArchive> OpenFile(uint32_t FileIdx) override;

        std::unique_ptr<Objects::UPackage> ExportPackage(uint32_t AssetIdx, Vfs::Vfs& Vfs) override;

        std::unique_ptr<Objects::UPackage> ExportPackageMinimal(uint32_t AssetIdx, Vfs::Vfs& Vfs) override;

        void Append(Vfs::Vfs& Vfs, bool TranslatePaths) override;

    private:
        friend class upp::Objects::FPakArchiveReaderBase;

        const Objects::FAESSchedule& GetSchedule() const;

        std::unique_ptr<char[]> GetIndexArchive(int64_t Offset, int64_t Size, const Objects::FSHAHash& Hash);

        Objects::FPakEntry DecodePakEntry(uint32_t Offset) const;

        void ReadIndex();

        void ReadIndexLegacy();

        Objects::FPakInfo Info;

        Vfs::Directory<> Index;

        std::variant<std::vector<Objects::FPakEntry>, std::unique_ptr<char[]>> EntryData;
    };
}