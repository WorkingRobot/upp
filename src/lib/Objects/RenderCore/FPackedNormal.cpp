#include "FPackedNormal.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FPackedNormal& Value)
    {
        Ar >> Value.Packed;

        return Ar;
    }
}