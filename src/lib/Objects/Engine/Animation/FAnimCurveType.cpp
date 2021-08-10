#include "FAnimCurveType.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FAnimCurveType& Value)
    {
        int bMaterial;
        Ar >> bMaterial;
        Value.Material = bMaterial;
        int bMorphtarget; // Don't ask why they made it lowercase
        Ar >> bMorphtarget;
        Value.MorphTarget = bMorphtarget;

        return Ar;
    }
}