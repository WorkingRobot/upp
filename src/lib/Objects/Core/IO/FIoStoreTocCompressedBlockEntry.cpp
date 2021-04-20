#include "FIoStoreTocCompressedBlockEntry.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FIoStoreTocCompressedBlockEntry& Value)
    {
        Ar >> Value.Data;

        return Ar;
    }
}