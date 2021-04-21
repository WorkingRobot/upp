#include "FIoStoreTocResource.h"

#include "../Serialization/FByteArchive.h"

namespace upp::Objects {
    void FIoStoreTocResource::Serialize(FArchive& Ar, const IKeyChain& KeyChain)
    {
        Ar >> Header;
        if (!Header.Magic.IsValid()) {
            return;
        }

        Ar.ReadBuffer(ChunkIds, Header.TocEntryCount);
        Ar.ReadBuffer(ChunkOffsetLengths, Header.TocEntryCount);
        Ar.ReadBuffer(CompressionBlocks, Header.TocCompressedBlockEntryCount);

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
            Ar.ReadBuffer(ChunkMetas, Header.TocEntryCount);
        }

        if (Header.Version < EIoStoreTocVersion::PartitionSize) {
            Header.PartitionCount = 1;
            Header.PartitionSize = std::numeric_limits<uint64_t>::max();
        }
    }
}