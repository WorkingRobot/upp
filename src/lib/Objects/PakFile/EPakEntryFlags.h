#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class EPakEntryFlags : uint8_t {
        None = 0x00,
        Encrypted = 0x01,
        Deleted = 0x02
    };
}