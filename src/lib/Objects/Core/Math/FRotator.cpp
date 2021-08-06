#include "FRotator.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FRotator& Value)
    {
        Ar >> Value.Pitch;
        Ar >> Value.Yaw;
        Ar >> Value.Roll;

        return Ar;
    }
}