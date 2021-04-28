#pragma once

#include <stdint.h>

namespace upp::Providers::Usmap {
    enum class ECompressionMethod : uint8_t {
        None,
        Oodle,
        Brotli,

        Unknown = 0xFF
    };
}