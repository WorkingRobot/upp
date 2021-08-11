#include "FSkeletalMeshSamplingLODBuiltData.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FSkeletalMeshSamplingLODBuiltData& Value)
    {
        Ar >> Value.AreaWeightedTriangleSampler;

        return Ar;
    }
}