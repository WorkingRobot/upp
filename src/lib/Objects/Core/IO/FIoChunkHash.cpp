#include "FIoChunkHash.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FIoChunkHash& Value)
    {
        Ar >> Value.Hash;

        return Ar;
    }
}