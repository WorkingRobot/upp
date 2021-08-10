#include "FReferenceSkeleton.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FReferenceSkeleton& Value)
    {
        Ar >> Value.RefBoneInfo;
        Ar >> Value.RefBonePose;
        Ar >> Value.NameToIndexMap;

        return Ar;
    }
}