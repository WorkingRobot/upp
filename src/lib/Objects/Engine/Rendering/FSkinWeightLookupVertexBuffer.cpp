#include "FSkinWeightLookupVertexBuffer.h"

#include "../FStripDataFlags.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FSkinWeightLookupVertexBuffer& Value)
    {
        FStripDataFlags StripFlags;
        Ar >> StripFlags;

        Ar >> Value.NumVertices;

        if (!StripFlags.IsDataStrippedForServer()) {
            Ar.BulkSerialize(Value.LookupData);
        }

        return Ar;
    }
}