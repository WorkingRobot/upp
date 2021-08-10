#include "FQuat.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FQuat& Value)
    {
        Ar >> Value.X;
        Ar >> Value.Y;
        Ar >> Value.Z;
        Ar >> Value.W;

        return Ar;
    }
}