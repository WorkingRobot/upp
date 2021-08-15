#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class ERenderTargetStoreAction : uint8_t {
        // Contents of the render target emitted during the pass are not stored back to memory.
        ENoAction,

        // Contents of the render target emitted during the pass are stored back to memory.
        EStore,

        // Contents of the render target emitted during the pass are resolved using a box filter and stored back to memory.
        EMultisampleResolve,

        Num,
        NumBits = 2,
    };
    static_assert((uint8_t)ERenderTargetStoreAction::Num <= (1 << (uint8_t)ERenderTargetStoreAction::NumBits), "ERenderTargetStoreAction::Num will not fit on ERenderTargetStoreAction::NumBits");
}