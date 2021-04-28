#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class EMappedNameType : uint8_t {
		Package,
		Container,
		Global
    };
}