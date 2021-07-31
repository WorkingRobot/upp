#include "FLinearColor.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FLinearColor& Value)
    {
        Ar >> Value.R;
        Ar >> Value.G;
        Ar >> Value.B;
        Ar >> Value.A;

        return Ar;
    }
}