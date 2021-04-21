#include "FPackageId.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FPackageId& Value)
    {
        Ar >> Value.Id;

        return Ar;
    }
}