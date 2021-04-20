#pragma once

#include "../Serialization/FArchive.h"
#include "FIoChunkHash.h"
#include "EIoStoreTocEntryMetaFlags.h"

namespace upp::Objects {
    struct FIoStoreTocEntryMeta {
        FIoChunkHash ChunkHash;
        EIoStoreTocEntryMetaFlags Flags;

        friend FArchive& operator>>(FArchive& Ar, FIoStoreTocEntryMeta& Value);
    };
}