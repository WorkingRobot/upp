#include "FSerializedNameHeader.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FSerializedNameHeader& Value)
    {
        uint16_t Val;
        Ar >> Val;

        Value.IsUtf16 = (Val & 0x80) != 0;
        Value.Len = ((Val & 0x7F) << 8) | ((Val & 0xFF00) >> 8);

        return Ar;
    }
}