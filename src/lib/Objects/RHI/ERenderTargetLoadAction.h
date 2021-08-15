#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class ERenderTargetLoadAction : uint8_t {
        // Untouched contents of the render target are undefined. Any existing content is not preserved.
        ENoAction,

        // Existing contents are preserved.
        ELoad,

        // The render target is cleared to the fast clear value specified on the resource.
        EClear,

        Num,
        NumBits = 2,
    };
    static_assert((uint8_t)ERenderTargetLoadAction::Num <= (1 << (uint8_t)ERenderTargetLoadAction::NumBits), "ERenderTargetLoadAction::Num will not fit on ERenderTargetLoadAction::NumBits");
}