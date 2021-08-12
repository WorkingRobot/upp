#include "FEntityAndMetaDataIndex.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FEntityAndMetaDataIndex& Value)
    {
        Ar >> Value.EntityIndex;
        Ar >> Value.MetaDataIndex;

        return Ar;
    }
}