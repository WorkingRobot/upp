#include "FSerializedNameHeader.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FSerializedNameHeader& Value)
    {
        Ar >> Value.Data;

        return Ar;
    }
}