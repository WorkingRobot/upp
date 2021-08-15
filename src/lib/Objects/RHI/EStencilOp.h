#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class EStencilOp : uint8_t {
        SO_Keep,
        SO_Zero,
        SO_Replace,
        SO_SaturatedIncrement,
        SO_SaturatedDecrement,
        SO_Invert,
        SO_Increment,
        SO_Decrement,

        EStencilOp_Num,
        EStencilOp_NumBits = 3,
    };
    static_assert((uint8_t)EStencilOp::EStencilOp_Num <= (1 << (uint8_t)EStencilOp::EStencilOp_NumBits), "EStencilOp_Num will not fit on EStencilOp_NumBits");
}