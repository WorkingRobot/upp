#include "FPlane.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FPlane& Value)
    {
        Ar >> (FVector&)Value;
        Ar >> Value.W;

        return Ar;
    }
}