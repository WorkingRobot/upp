#pragma once

#include "../Serialization/FArchive.h"
#include "../Misc/FGuid.h"
#include "EIoContainerFlags.h"
#include "EIoStoreTocVersion.h"
#include "FIoContainerId.h"

namespace upp::Objects {
    struct FIoStoreTocHeader {
        static constexpr FGuid FileMagic = FGuid(0x2D3D3D2D);
        static constexpr uint32_t HeaderSize = 144;

        FGuid Magic;
        EIoStoreTocVersion Version;
        uint32_t TocHeaderSize;
        uint32_t TocEntryCount;
        uint32_t TocCompressedBlockEntryCount;
        uint32_t TocCompressedBlockEntrySize;
        uint32_t CompressionMethodNameCount;
        uint32_t CompressionMethodNameLength;
        uint32_t CompressionBlockSize;
        FIoContainerId ContainerId;
        FGuid EncryptionKeyGuid;
        EIoContainerFlags ContainerFlags;

        uint32_t DirectoryIndexSize;

        uint32_t PartitionCount;
        uint64_t PartitionSize;

        // https://github.com/EpicGames/UnrealEngine/blob/94d91f5af6206c563300b2279227161bcb1b7ddf/Engine/Source/Runtime/Core/Private/IO/IoStore.h#L44
        // https://github.com/EpicGames/UnrealEngine/blob/94d91f5af6206c563300b2279227161bcb1b7ddf/Engine/Source/Runtime/Core/Private/IO/IoStore.cpp#1666
        // What do you think FArchive is here for? PepeLaugh
        friend FArchive& operator>>(FArchive& Ar, FIoStoreTocHeader& Value);
    };
}