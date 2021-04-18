#pragma once

#include <stdint.h>

namespace upp {
    template<class N>
    static constexpr N Align(N Value, uint64_t Alignment) {
        return (N)(((uint64_t)Value + Alignment - 1) & ~(Alignment - 1));
    }

    template<uint64_t Alignment, class N>
    static constexpr N Align(N Value) {
        return (N)(((uint64_t)Value + Alignment - 1) & ~(Alignment - 1));
    }
}