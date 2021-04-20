#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class EIoContainerFlags : uint8_t {
        None = 0x00,
        Compressed = 0x01,
        Encrypted = 0x02,
        Signed = 0x04,
        Indexed = 0x08,
    };
}