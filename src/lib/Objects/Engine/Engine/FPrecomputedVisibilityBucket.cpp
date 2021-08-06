#include "FPrecomputedVisibilityBucket.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FPrecomputedVisibilityBucket& Value)
    {
        Ar >> Value.CellDataSize;
        Ar >> Value.Cells;
        Ar >> Value.CellDataChunks;

        return Ar;
    }
}