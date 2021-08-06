#include "FVector4.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FVector4& Value)
    {
        Ar >> Value.X;
        Ar >> Value.Y;
        Ar >> Value.Z;
        Ar >> Value.W;

        return Ar;
    }
}