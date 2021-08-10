#include "FMeshBoneInfo.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FMeshBoneInfo& Value)
    {
        Ar >> Value.Name;
        Ar >> Value.ParentIndex;

        return Ar;
    }
}