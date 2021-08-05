#include "FImplementedInterface.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FImplementedInterface& Value)
    {
        Ar >> Value.Class;
        Ar >> Value.PointerOffset;
        int bImplementedByK2;
        Ar >> bImplementedByK2;
        Value.IsImplementedByK2 = bImplementedByK2;

        return Ar;
    }
}