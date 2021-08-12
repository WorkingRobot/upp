#include "FEntry.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FEntry& Value)
    {
        Ar >> Value.StartIndex;
        Ar >> Value.Size;
        Ar >> Value.Capacity;

        return Ar;
    }
}