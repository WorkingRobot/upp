#include "FIoOffsetAndLength.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FIoOffsetAndLength& Value)
    {
        Ar >> Value.OffsetAndLength;

        return Ar;
    }
}