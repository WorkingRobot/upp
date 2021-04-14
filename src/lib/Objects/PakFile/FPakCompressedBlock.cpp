#include "FPakCompressedBlock.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FPakCompressedBlock& Value)
    {
        Ar >> Value.CompressedStart;
        Ar >> Value.CompressedEnd;

        return Ar;
    }
}