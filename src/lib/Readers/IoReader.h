#pragma once

#include "../Objects/CoreUObject/Serialization/FContainerHeader.h"
#include "../Objects/Core/IO/FIoStoreTocResource.h"
#include "../Vfs/Directory.h"
#include "../Compression.h"
#include "BaseReader.h"

namespace upp::Objects {
    class FIoArchive;
}

namespace upp::Readers {
    class IoReader : public BaseReader {
    public:
        // As of right now, partitioned ucas files aren't supported
        // https://github.com/EpicGames/UnrealEngine/blob/94d91f5af6206c563300b2279227161bcb1b7ddf/Engine/Source/Runtime/Core/Private/IO/IoStore.cpp#L1365
        IoReader(Objects::FArchive& Archive, Objects::FArchive& TocArchive, const IKeyChain& KeyChain, uint32_t ReaderIdx = -1);

        IoReader(Objects::FArchive& Archive, Objects::FIoStoreTocResource&& Toc, const IKeyChain& KeyChain, uint32_t ReaderIdx = -1);

        CompressionMethod GetCompressionMethod(uint32_t CompressionMethodIdx) const;

        Objects::FContainerHeader* GetHeader();

        uint32_t FindChunk(const Objects::FIoChunkId& Id) const override;

        std::unique_ptr<Objects::FArchive> OpenFile(uint32_t FileIdx) override;

        std::unique_ptr<Objects::UPackage> ExportPackage(uint32_t AssetIdx, Vfs::Vfs& Vfs) override;

        std::unique_ptr<Objects::UPackage> ExportPackageMinimal(uint32_t AssetIdx, Vfs::Vfs& Vfs) override;

        void Append(Vfs::Vfs& Vfs, bool TranslatePaths) override;

    private:
        friend class upp::Objects::FIoArchive;

        void Construct(Objects::FIoStoreTocResource&& Toc);

        const Objects::FAESSchedule& GetSchedule() const;

        void Append(const Objects::FIoDirectoryIndexResource& Index, Vfs::Directory<>& Tree, uint32_t DirIdx);

        Vfs::Directory<> Index;

        Objects::FIoContainerId ContainerId;
        Objects::EIoContainerFlags ContainerFlags;
        uint32_t CompressionBlockSize;
        uint64_t PartitionSize;
        Objects::FGuid EncryptionKeyGuid;
        std::vector<CompressionMethod> CompressionMethods;
        std::vector<Objects::FIoOffsetAndLength> ChunkOffsetLengths;
        std::vector<Objects::FIoChunkId> ChunkIds;
        std::vector<Objects::FIoStoreTocCompressedBlockEntry> CompressionBlocks;
        std::optional<Objects::FContainerHeader> Header;

        std::unordered_map<std::reference_wrapper<const Objects::FIoChunkId>, uint32_t, std::hash<Objects::FIoChunkId>> ChunkIdLUT;
    };
}