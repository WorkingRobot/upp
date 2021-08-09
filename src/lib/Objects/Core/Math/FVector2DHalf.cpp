#include "FVector2DHalf.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FVector2DHalf& Value)
    {
        Ar >> Value.X;
        Ar >> Value.Y;

        return Ar;
    }
}