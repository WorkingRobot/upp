#pragma once

#include "../Serialization/FArchive.h"

namespace upp::Objects {
	struct FDateTime {
		int64_t Ticks;

		friend FArchive& operator>>(FArchive& Ar, FDateTime& Value) {
			Ar >> Value.Ticks;

			return Ar;
		}
	};
}