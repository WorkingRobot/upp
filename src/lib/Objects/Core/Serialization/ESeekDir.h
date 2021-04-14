#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class ESeekDir : uint8_t {
        Beg,
        Cur,
        End
    };
}