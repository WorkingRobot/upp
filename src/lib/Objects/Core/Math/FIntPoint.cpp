#include "FIntPoint.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FIntPoint& Value)
    {
        Ar >> Value.X;
        Ar >> Value.Y;

        return Ar;
    }
}