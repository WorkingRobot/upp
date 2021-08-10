#include "FTransform.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FTransform& Value)
    {
        Ar >> Value.Rotation;
        Ar >> Value.Translation;
        Ar >> Value.Scale3D;

        return Ar;
    }
}