#pragma once

#include <stdint.h>

namespace upp::Readers {
    enum class SeekDir : uint8_t {
        Beg,
        Cur,
        End
    };
}