#include "FVector.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FVector& Value)
    {
        Ar >> Value.X;
        Ar >> Value.Y;
        Ar >> Value.Z;

        return Ar;
    }
}