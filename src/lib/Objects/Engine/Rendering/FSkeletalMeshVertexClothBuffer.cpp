#include "FSkeletalMeshVertexClothBuffer.h"

#include "../FStripDataFlags.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FSkeletalMeshVertexClothBuffer& Value)
    {
        FStripDataFlags StripFlags;
        Ar >> StripFlags;

        if (!StripFlags.IsDataStrippedForServer()) {
            Ar.BulkSerialize(Value.VertexData);

            Ar >> Value.ClothIndexMapping;
        }

        return Ar;
    }
}