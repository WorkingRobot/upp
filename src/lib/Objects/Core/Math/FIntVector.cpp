#include "FIntVector.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FIntVector& Value)
    {
        Ar >> Value.X;
        Ar >> Value.Y;
        Ar >> Value.Z;

        return Ar;
    }
}