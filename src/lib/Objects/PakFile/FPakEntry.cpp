#include "FPakEntry.h"

#include "../Core/Misc/FDateTime.h"

namespace upp::Objects {
    void FPakEntry::Serialize(FArchive& Ar, EPakVersion Version)
    {
        Ar >> Offset;
        Ar >> Size;
        Ar >> UncompressedSize;

        if (Version >= EPakVersion::FNameBasedCompressionMethod) {
            Ar >> CompressionMethodIndex;
        }
        else {
            int LegacyCompressionMethod;
            Ar >> LegacyCompressionMethod;
            // ECompressionFlags from UE4
            switch (LegacyCompressionMethod)
            {
            case 0x00:
                CompressionMethodIndex = 0;
                break;
            case 0x01:
                CompressionMethodIndex = 1;
                break;
            case 0x02:
                CompressionMethodIndex = 2;
                break;
            case 0x04:
                CompressionMethodIndex = 3;
                break;
            default:
                // Unknown legacy compression type
                CompressionMethodIndex = -1;
                return;
            }
        }

        if (Version < EPakVersion::NoTimestamps) {
            FDateTime Timestamp;
            Ar >> Timestamp;
        }

        Ar >> Hash;

        if (Version >= EPakVersion::CompressionEncryption) {
            if (CompressionMethodIndex != 0) {
                Ar >> CompressionBlocks;
            }
            Ar >> Flags;
            Ar >> CompressionBlockSize;
        }
    }
}