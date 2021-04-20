#include "FIoStoreTocResource.h"

#include "../Serialization/FByteArchive.h"

namespace upp::Objects {
    void FIoStoreTocResource::Serialize(FArchive& Ar, const IKeyChain& KeyChain)
    {
        Ar >> Header;
        if (!Header.Magic.IsValid()) {
            return;
        }

        static_assert(std::has_unique_object_representations_v<FIoChunkId>, "Ar.Read must be changed to a for loop");
        ChunkIds.resize(Header.TocEntryCount);
        Ar.Read((char*)ChunkIds.data(), Header.TocEntryCount * sizeof(FIoChunkId));

        static_assert(std::has_unique_object_representations_v<FIoOffsetAndLength>, "Ar.Read must be changed to a for loop");
        ChunkOffsetLengths.resize(Header.TocEntryCount);
        Ar.Read((char*)ChunkOffsetLengths.data(), Header.TocEntryCount * sizeof(FIoOffsetAndLength));

        static_assert(std::has_unique_object_representations_v<FIoStoreTocCompressedBlockEntry>, "Ar.Read must be changed to a for loop");
        CompressionBlocks.resize(Header.TocCompressedBlockEntryCount);
        Ar.Read((char*)CompressionBlocks.data(), Header.TocCompressedBlockEntryCount * sizeof(FIoStoreTocCompressedBlockEntry));

        {
            CompressionMethods.emplace_back("None");
            auto BufferSize = Header.CompressionMethodNameLength * Header.CompressionMethodNameCount;
            auto Methods = std::make_unique<char[]>(BufferSize);
            Ar.Read(Methods.get(), BufferSize);
            for (int i = 0; i < BufferSize; i += Header.CompressionMethodNameLength) {
                CompressionMethods.emplace_back(Methods.get() + i);
            }
        }

        if ((uint8_t)Header.ContainerFlags & (uint8_t)EIoContainerFlags::Signed) {
            int32_t HashSize;
            Ar >> HashSize;
            auto TocSignature = std::make_unique<char[]>(HashSize);
            auto BlockSignature = std::make_unique<char[]>(HashSize);
            Ar.Read(TocSignature.get(), HashSize);
            Ar.Read(BlockSignature.get(), HashSize);

            ChunkBlockSignatures.resize(Header.TocCompressedBlockEntryCount);
            Ar.Read((char*)ChunkBlockSignatures.data(), Header.TocCompressedBlockEntryCount * sizeof(FSHAHash));

            // Validate signatures here
        }

        if ((uint8_t)Header.ContainerFlags & (uint8_t)EIoContainerFlags::Indexed && Header.DirectoryIndexSize != 0) {
            auto IdxData = std::make_unique<char[]>(Header.DirectoryIndexSize);
            Ar.Read(IdxData.get(), Header.DirectoryIndexSize);

            if ((uint8_t)Header.ContainerFlags & (uint8_t)EIoContainerFlags::Encrypted) {
                auto& Schedule = KeyChain.GetKey(Header.EncryptionKeyGuid);
                if (Schedule.IsValid()) {
                    Schedule.DecryptInPlace(IdxData.get(), Header.DirectoryIndexSize);
                }
            }

            FByteArchive IdxAr(std::move(IdxData), Header.DirectoryIndexSize, Ar.GetName() + " Index");
            IdxAr >> DirectoryIndex;
        }

        {
            static_assert(std::has_unique_object_representations_v<FIoStoreTocEntryMeta>, "Ar.Read must be changed to a for loop");
            ChunkMetas.resize(Header.TocEntryCount);
            Ar.Read((char*)ChunkMetas.data(), Header.TocEntryCount * sizeof(FIoStoreTocEntryMeta));
        }

        if (Header.Version < EIoStoreTocVersion::PartitionSize) {
            Header.PartitionCount = 1;
            Header.PartitionSize = std::numeric_limits<uint64_t>::max();
        }

    }
}