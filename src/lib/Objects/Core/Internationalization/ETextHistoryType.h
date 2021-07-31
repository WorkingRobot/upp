#pragma once

#include <stdint.h>

namespace upp::Objects {
	enum class ETextHistoryType : int8_t
	{
		None = -1,
		Base = 0,
		NamedFormat,
		OrderedFormat,
		ArgumentFormat,
		AsNumber,
		AsPercent,
		AsCurrency,
		AsDate,
		AsTime,
		AsDateTime,
		Transform,
		StringTableEntry,
		TextGenerator

		// Add new enum types at the end only! They are serialized by index.
	};
}