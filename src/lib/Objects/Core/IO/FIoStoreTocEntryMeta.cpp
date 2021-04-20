#include "FIoStoreTocEntryMeta.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FIoStoreTocEntryMeta& Value)
    {
        Ar >> Value.ChunkHash;
        Ar >> Value.Flags;

        return Ar;
    }
}