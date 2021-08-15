#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class ECompareFunction : uint8_t {
        CF_Less,
        CF_LessEqual,
        CF_Greater,
        CF_GreaterEqual,
        CF_Equal,
        CF_NotEqual,
        CF_Never,
        CF_Always,

        ECompareFunction_Num,
        ECompareFunction_NumBits = 3,

        // Utility enumerations
        //CF_DepthNearOrEqual = (((int32)ERHIZBuffer::IsInverted != 0) ? CF_GreaterEqual : CF_LessEqual),
        //CF_DepthNear = (((int32)ERHIZBuffer::IsInverted != 0) ? CF_Greater : CF_Less),
        //CF_DepthFartherOrEqual = (((int32)ERHIZBuffer::IsInverted != 0) ? CF_LessEqual : CF_GreaterEqual),
        //CF_DepthFarther = (((int32)ERHIZBuffer::IsInverted != 0) ? CF_Less : CF_Greater),
    };
    static_assert((uint8_t)ECompareFunction::ECompareFunction_Num <= (1 << (uint8_t)ECompareFunction::ECompareFunction_NumBits), "ECompareFunction_Num will not fit on ECompareFunction_NumBits");
}