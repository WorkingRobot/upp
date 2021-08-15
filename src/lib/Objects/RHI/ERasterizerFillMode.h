#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class ERasterizerFillMode : uint8_t {
        FM_Point,
        FM_Wireframe,
        FM_Solid,

        ERasterizerFillMode_Num,
        ERasterizerFillMode_NumBits = 2,
    };
    static_assert((uint8_t)ERasterizerFillMode::ERasterizerFillMode_Num <= (1 << (uint8_t)ERasterizerFillMode::ERasterizerFillMode_NumBits), "ERasterizerFillMode_Num will not fit on ERasterizerFillMode_NumBits");
}