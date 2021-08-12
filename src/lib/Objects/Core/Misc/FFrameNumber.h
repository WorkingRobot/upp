#pragma once

#include "../Serialization/FArchive.h"

namespace upp::Objects {
	struct FFrameNumber {
		int Value;

		friend FArchive& operator>>(FArchive& Ar, FFrameNumber& Value) {
			Ar >> Value.Value;

			return Ar;
		}
	};
}