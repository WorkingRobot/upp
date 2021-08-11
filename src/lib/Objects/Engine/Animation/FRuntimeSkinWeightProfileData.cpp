#include "FRuntimeSkinWeightProfileData.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FRuntimeSkinWeightProfileData& Value)
    {
        Ar >> Value.BoneIDs;
        Ar >> Value.BoneWeights;
        Ar >> Value.NumWeightsPerVertex;
        Ar >> Value.VertexIndexToInfluenceOffset;

        return Ar;
    }
}