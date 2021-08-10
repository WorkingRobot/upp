#include "FCurveMetaData.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FCurveMetaData& Value)
    {
        Ar >> Value.Type;
        Ar >> Value.LinkedBones;
        Ar >> Value.MaxLOD;

        return Ar;
    }
}