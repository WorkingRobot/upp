#include "FPakInfo.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FPakInfo& Value)
    {
        Ar >> Value.EncryptionKeyGuid;
        Ar >> Value.IsEncryptedIndex;

        Ar >> Value.Magic;
        if (Value.Magic != FPakInfo::FileMagic) {
            Value.Magic = 0;
            return Ar;
        }

        Ar >> Value.Version;
        Ar >> Value.IndexOffset;
        Ar >> Value.IndexSize;
        Ar >> Value.IndexHash;

        if (Value.Version < EPakVersion::IndexEncryption) {
            Value.IsEncryptedIndex = false;
        }
        if (Value.Version < EPakVersion::EncryptionKeyGuid) {
            Value.EncryptionKeyGuid.Invalidate();
        }

        if (Value.Version == EPakVersion::FrozenIndex) {
            bool IsIndexFrozen;
            Ar >> IsIndexFrozen;
            if (IsIndexFrozen) {
                return Ar;
            }
        }

        if (Value.Version < EPakVersion::FNameBasedCompressionMethod) {
            Value.CompressionMethods = { "None", "Zlib", "Gzip", "Oodle" };
        }
        else {
            Value.CompressionMethods.emplace_back("None");

            constexpr int BufferSize = FPakInfo::CompressionMethodNameLen * FPakInfo::CompressionMethodMaxCount;
            char Methods[BufferSize];
            Ar.Read(Methods, BufferSize);
            for (int i = 0; i < BufferSize; i += FPakInfo::CompressionMethodNameLen) {
                char* MethodString = Methods + i;
                if (*MethodString) {
                    Value.CompressionMethods.emplace_back(MethodString);
                }
            }
        }

        return Ar;
    }
}