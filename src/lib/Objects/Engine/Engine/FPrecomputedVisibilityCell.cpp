#include "FPrecomputedVisibilityCell.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FPrecomputedVisibilityCell& Value)
    {
        Ar >> Value.Min;
        Ar >> Value.ChunkIndex;
        Ar >> Value.DataOffset;

        return Ar;
    }
}