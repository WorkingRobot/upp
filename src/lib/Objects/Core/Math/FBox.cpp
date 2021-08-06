#include "FBox.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FBox& Value)
    {
        Ar >> Value.Min;
        Ar >> Value.Max;
        Ar >> Value.IsValid;

        return Ar;
    }
}