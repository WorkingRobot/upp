#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class EColorWriteMask : uint8_t {
        CW_RED = 0x01,
        CW_GREEN = 0x02,
        CW_BLUE = 0x04,
        CW_ALPHA = 0x08,

        CW_NONE = 0,
        CW_RGB = CW_RED | CW_GREEN | CW_BLUE,
        CW_RGBA = CW_RED | CW_GREEN | CW_BLUE | CW_ALPHA,
        CW_RG = CW_RED | CW_GREEN,
        CW_BA = CW_BLUE | CW_ALPHA,

        EColorWriteMask_NumBits = 4,
    };
}