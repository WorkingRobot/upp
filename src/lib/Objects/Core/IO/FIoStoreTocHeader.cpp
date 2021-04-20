#include "FIoStoreTocHeader.h"

#include "FIoStoreTocCompressedBlockEntry.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FIoStoreTocHeader& Value)
    {
        Ar >> Value.Magic;
        if (Value.Magic != FIoStoreTocHeader::FileMagic) {
            Value.Magic.Invalidate();
            return Ar;
        }

        // Seeks are for alignment
        Ar >> Value.Version;
        Ar.Seek(3, ESeekDir::Cur);

        Ar >> Value.TocHeaderSize;
        Ar >> Value.TocEntryCount;
        Ar >> Value.TocCompressedBlockEntryCount;
        Ar >> Value.TocCompressedBlockEntrySize;
        Ar >> Value.CompressionMethodNameCount;
        Ar >> Value.CompressionMethodNameLength;
        Ar >> Value.CompressionBlockSize;
        Ar >> Value.DirectoryIndexSize;
        Ar >> Value.PartitionCount;
        Ar >> Value.ContainerId;
        Ar >> Value.EncryptionKeyGuid;

        Ar >> Value.ContainerFlags;
        Ar.Seek(7, ESeekDir::Cur);

        Ar >> Value.PartitionSize;
        Ar.Seek(48, ESeekDir::Cur);

        if (Value.HeaderSize != FIoStoreTocHeader::HeaderSize) {
            Value.Magic.Invalidate();
            return Ar;
        }

        if (Value.TocCompressedBlockEntrySize != sizeof(FIoStoreTocCompressedBlockEntry)) {
            Value.Magic.Invalidate();
            return Ar;
        }

        if (Value.Version < EIoStoreTocVersion::DirectoryIndex) {
            Value.Magic.Invalidate();
            return Ar;
        }

        return Ar;
    }
}