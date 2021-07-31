#include "FUniqueObjectGuid.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FUniqueObjectGuid& Value)
    {
        Ar >> (FGuid&)Value;

        return Ar;
    }
}