#include "FIoChunkId.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FIoChunkId& Value)
    {
        Ar >> Value.Id;

        return Ar;
    }
}