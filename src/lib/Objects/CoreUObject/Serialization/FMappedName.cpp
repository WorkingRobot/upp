#include "FMappedName.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FMappedName& Value)
    {
        Ar >> Value.Index;
        Ar >> Value.Number;

        return Ar;
    }
}