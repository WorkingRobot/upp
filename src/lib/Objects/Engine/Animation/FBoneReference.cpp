#include "FBoneReference.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FBoneReference& Value)
    {
        Ar >> Value.BoneName;

        return Ar;
    }
}