#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class EBlendOperation : uint8_t {
        BO_Add,
        BO_Subtract,
        BO_Min,
        BO_Max,
        BO_ReverseSubtract,

        EBlendOperation_Num,
        EBlendOperation_NumBits = 3,
    };
    static_assert((uint8_t)EBlendOperation::EBlendOperation_Num <= (1 << (uint8_t)EBlendOperation::EBlendOperation_NumBits), "EBlendOperation_Num will not fit on EBlendOperation_NumBits");
}