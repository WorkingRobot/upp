#include "FBoxSphereBounds.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FBoxSphereBounds& Value)
    {
        Ar >> Value.Origin;
        Ar >> Value.BoxExtent;
        Ar >> Value.SphereRadius;

        return Ar;
    }
}