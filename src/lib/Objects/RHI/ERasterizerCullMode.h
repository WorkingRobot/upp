#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class ERasterizerCullMode : uint8_t {
        CM_None,
        CM_CW,
        CM_CCW,

        ERasterizerCullMode_Num,
        ERasterizerCullMode_NumBits = 2,
    };
    static_assert((uint8_t)ERasterizerCullMode::ERasterizerCullMode_Num <= (1 << (uint8_t)ERasterizerCullMode::ERasterizerCullMode_NumBits), "ERasterizerCullMode_Num will not fit on ERasterizerCullMode_NumBits");
}