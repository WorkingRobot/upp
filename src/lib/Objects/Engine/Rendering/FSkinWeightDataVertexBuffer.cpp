#include "FSkinWeightDataVertexBuffer.h"

#include "../FStripDataFlags.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FSkinWeightDataVertexBuffer& Value)
    {
        FStripDataFlags StripFlags;
        Ar >> StripFlags;

        int bVariableBonesPerVertex;
        Ar >> bVariableBonesPerVertex;
        Value.VariableBonesPerVertex = bVariableBonesPerVertex;

        Ar >> Value.MaxBoneInfluences;
        Ar >> Value.NumBones;
        Ar >> Value.NumVertices;

        int bUse16BitBoneIndex;
        Ar >> bUse16BitBoneIndex;
        Value.Use16BitBoneIndex = bUse16BitBoneIndex;

        if (!StripFlags.IsDataStrippedForServer()) {
            Ar.BulkSerialize(Value.WeightData);
        }

        return Ar;
    }
}