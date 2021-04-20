#include "FIoContainerId.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FIoContainerId& Value)
    {
        Ar >> Value.Id;

        return Ar;
    }
}