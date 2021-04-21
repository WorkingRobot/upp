#include "FPackageObjectIndex.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FPackageObjectIndex& Value)
    {
        Ar >> Value.TypeAndId;

        return Ar;
    }
}