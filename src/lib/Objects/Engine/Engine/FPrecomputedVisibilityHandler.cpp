#include "FPrecomputedVisibilityHandler.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FPrecomputedVisibilityHandler& Value)
    {
        Ar >> Value.PrecomputedVisibilityCellBucketOriginXY;
        Ar >> Value.PrecomputedVisibilityCellSizeXY;
        Ar >> Value.PrecomputedVisibilityCellSizeZ;
        Ar >> Value.PrecomputedVisibilityCellBucketSizeXY;
        Ar >> Value.PrecomputedVisibilityNumCellBuckets;
        Ar >> Value.PrecomputedVisibilityCellBuckets;

        return Ar;
    }
}