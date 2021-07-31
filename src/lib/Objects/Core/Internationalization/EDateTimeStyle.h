#pragma once

#include <stdint.h>

namespace upp::Objects {
	enum class EDateTimeStyle : int8_t {
		Default,
		Short,
		Medium,
		Long,
		Full
		// Add new enum types at the end only! They are serialized by index.
	};
}