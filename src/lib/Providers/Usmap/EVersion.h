#pragma once

#include <stdint.h>

namespace upp::Providers::Usmap {
    enum class EVersion : uint8_t {
        Initial,

        LatestPlusOne,
        Latest = LatestPlusOne - 1
    };
}