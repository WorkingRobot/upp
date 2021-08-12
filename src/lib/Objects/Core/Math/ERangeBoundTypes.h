#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class ERangeBoundTypes : uint8_t {
		/** The range excludes the bound. */
		Exclusive,
		/** The range includes the bound. */
		Inclusive,
		/** The bound is open. */
		Open
    };
}