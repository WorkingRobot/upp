#include "FFragment.h"

namespace upp::Objects {
    constexpr uint32_t SkipMax = 127;
    constexpr uint32_t ValueMax = 127;

    constexpr uint32_t SkipNumMask = 0x007fu;
    constexpr uint32_t HasZeroMask = 0x0080u;
    constexpr uint32_t ValueNumShift = 9u;
    constexpr uint32_t IsLastMask = 0x0100u;

    FArchive& operator>>(FArchive& Ar, FFragment& Value)
    {
        uint16_t Val;
        Ar >> Val;

        // AAAAAAAB CDDDDDDD
        // A = SkipNum, B = HasAnyZeroes, C = IsLast, ValueNum = D
        Value.SkipNum = uint8_t(Val & SkipNumMask);
        Value.HasAnyZeroes = (Val & HasZeroMask) != 0;
        Value.ValueNum = uint8_t(Val >> ValueNumShift);
        Value.IsLast = (Val & IsLastMask) != 0;

        return Ar;
    }
}