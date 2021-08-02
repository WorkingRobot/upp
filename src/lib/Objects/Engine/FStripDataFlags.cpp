#include "FStripDataFlags.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FStripDataFlags& Value)
    {
        Ar >> Value.GlobalStripFlags;
        Ar >> Value.ClassStripFlags;

        return Ar;
    }
}