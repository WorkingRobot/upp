#include "FPackedRGBA16N.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FPackedRGBA16N& Value)
    {
        Ar >> Value.X;
        Ar >> Value.Y;
        Ar >> Value.Z;
        Ar >> Value.W;

        return Ar;
    }
}