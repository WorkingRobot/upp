#pragma once

#include "../Serialization/FArchive.h"

#include <immintrin.h>

namespace upp::Objects {
	struct FAESKey {
		__m256i Key;
		
		friend FArchive& operator>>(FArchive& Ar, FAESKey& Value) {
			Ar >> Value.Key.m256i_u8;

			return Ar;
		}

		bool IsValid() const
		{
			return !_mm256_testz_si256(Key, Key);
		}
	};
}