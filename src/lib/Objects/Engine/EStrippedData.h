#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class EStrippedData : uint8_t {
		None = 0,

		/* Editor data */
		Editor = 1,
		/* All data not required for dedicated server to work correctly (usually includes editor data). */
		Server = 2,

		// Add global flags here (up to 8 including the already defined ones).

		/** All flags */
		All = 0xff
    };
}