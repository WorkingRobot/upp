#pragma once

#include "../Core/Serialization/FArchive.h"
#include "../Core/Misc/FGuid.h"
#include "../Core/Misc/FSHAHash.h"
#include "EPakVersion.h"

namespace upp::Objects {
    struct FPakInfo {
        static constexpr uint32_t FileMagic = 0x5A6F12E1;
        static constexpr int CompressionMethodNameLen = 32;
        static constexpr int CompressionMethodMaxCount = 5;

        uint32_t Magic;

        EPakVersion Version;

        int64_t IndexOffset;

        int64_t IndexSize;

        FSHAHash IndexHash;

        bool IsEncryptedIndex;

        FGuid EncryptionKeyGuid;

        std::vector<std::string> CompressionMethods;

        friend FArchive& operator>>(FArchive& Ar, FPakInfo& Value);

        static constexpr size_t GetSerializedSize(EPakVersion Version = EPakVersion::Latest) {
            size_t Size = sizeof(Magic) + sizeof(Version) + sizeof(IndexOffset) + sizeof(IndexSize) + sizeof(IndexHash) + sizeof(IsEncryptedIndex);
            if (Version >= EPakVersion::EncryptionKeyGuid) {
                Size += sizeof(EncryptionKeyGuid);
            }
            if (Version >= EPakVersion::FNameBasedCompressionMethod) {
                Size += CompressionMethodNameLen * CompressionMethodMaxCount;
            }
            if (Version == EPakVersion::FrozenIndex) {
                Size += sizeof(bool);
            }

            return Size;
        }
    };
}