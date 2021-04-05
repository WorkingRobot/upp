#pragma once

#include "../Readers/FArchive.h"
#include "../Objects/Core/Misc/FGuid.h"
#include "../Objects/Core/Misc/FSHAHash.h"
#include "EPakVersion.h"

#include <vector>

namespace upp::Pak {
    struct FPakInfo {
        static constexpr uint32_t FileMagic = 0x5A6F12E1;
        static constexpr int CompressionMethodNameLen = 32;
        static constexpr int CompressionMethodMaxCount = 5;

        uint32_t Magic;

        EPakVersion Version;

        int64_t IndexOffset;

        int64_t IndexSize;

        Objects::FSHAHash IndexHash;

        bool IsEncryptedIndex;

        Objects::FGuid EncryptionKeyGuid;

        std::vector<std::string> CompressionMethods;

        friend Readers::FArchive& operator>>(Readers::FArchive& InputStream, FPakInfo& Value) {
            InputStream >> Value.EncryptionKeyGuid;
            InputStream >> Value.IsEncryptedIndex;

            InputStream >> Value.Magic;
            if (Value.Magic != FileMagic) {
                Value.Magic = 0;
                InputStream.SetError(Readers::FArchive::Error::InvalidMagic);
                return InputStream;
            }

            InputStream >> Value.Version;
            InputStream >> Value.IndexOffset;
            InputStream >> Value.IndexSize;
            InputStream >> Value.IndexHash;

            if (Value.Version < EPakVersion::IndexEncryption) {
                Value.IsEncryptedIndex = false;
            }
            if (Value.Version < EPakVersion::EncryptionKeyGuid) {
                Value.EncryptionKeyGuid.Invalidate();
            }

            if (Value.Version == EPakVersion::FrozenIndex) {
                bool IsIndexFrozen;
                InputStream >> IsIndexFrozen;
                if (IsIndexFrozen) {
                    InputStream.SetError(Readers::FArchive::Error::UnsupportedFrozenIndex);
                    return InputStream;
                }
            }

            if (Value.Version < EPakVersion::FNameBasedCompressionMethod) {
                Value.CompressionMethods = { "None", "Zlib", "Gzip", "Oodle" };
            }
            else {
                Value.CompressionMethods.emplace_back("None");

                constexpr int BufferSize = FPakInfo::CompressionMethodNameLen * FPakInfo::CompressionMethodMaxCount;
                char Methods[BufferSize];
                InputStream.Read(Methods, BufferSize);
                for (int i = 0; i < BufferSize; i += FPakInfo::CompressionMethodNameLen) {
                    char* MethodString = Methods + i;
                    if (*MethodString) {
                        Value.CompressionMethods.emplace_back(MethodString);
                    }
                }
            }

            return InputStream;
        }

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