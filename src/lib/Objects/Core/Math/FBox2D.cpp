#include "FBox2D.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FBox2D& Value)
    {
        Ar >> Value.Min;
        Ar >> Value.Max;
        Ar >> Value.IsValid;

        return Ar;
    }
}