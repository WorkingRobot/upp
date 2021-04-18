#pragma once

#include "../Core/Serialization/FArchive.h"
#include "../Core/Misc/FGuid.h"
#include "../Core/Misc/FSHAHash.h"
#include "FPakCompressedBlock.h"
#include "EPakEntryFlags.h"
#include "EPakVersion.h"

namespace upp::Objects {
    struct FPakEntry {
        int64_t Offset;

        int64_t Size;

        int64_t UncompressedSize;

        FSHAHash Hash;

        std::vector<FPakCompressedBlock> CompressionBlocks;

        uint32_t CompressionBlockSize;

        uint32_t CompressionMethodIndex;

        EPakEntryFlags Flags;

        void Serialize(FArchive& Ar, EPakVersion Version);

        bool IsEncrypted() const {
            return (uint8_t)Flags & (uint8_t)EPakEntryFlags::Encrypted;
        }

        constexpr size_t GetSerializedSize(EPakVersion Version = EPakVersion::Latest) const {
            size_t Size = sizeof(Offset) + sizeof(Size) + sizeof(UncompressedSize) + sizeof(Hash);
            if (Version >= EPakVersion::FNameBasedCompressionMethod) {
                Size += sizeof(CompressionMethodIndex);
            }
            else {
                Size += sizeof(int); // Old CompressionMethod indexes
            }

            if (Version >= EPakVersion::CompressionEncryption)
            {
                Size += sizeof(Flags) + sizeof(CompressionBlockSize);
                if (CompressionMethodIndex != 0)
                {
                    Size += sizeof(FPakCompressedBlock) * CompressionBlocks.size() + sizeof(int);
                }
            }
            if (Version < EPakVersion::NoTimestamps)
            {
                // Timestamp
                Size += sizeof(int64_t);
            }

            return Size;
        }
    };
}