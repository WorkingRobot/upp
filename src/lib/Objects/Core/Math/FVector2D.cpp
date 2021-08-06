#include "FVector2D.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FVector2D& Value)
    {
        Ar >> Value.X;
        Ar >> Value.Y;

        return Ar;
    }
}