#pragma once

#include "../../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FFragment {
        uint8_t SkipNum;
        bool HasAnyZeroes;
        uint8_t ValueNum;
        bool IsLast;

        friend FArchive& operator>>(FArchive& Ar, FFragment& Value);
    };
}