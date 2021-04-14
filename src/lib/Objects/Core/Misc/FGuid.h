#pragma once

#include "../Serialization/FArchive.h"

namespace upp::Objects {
	struct FGuid {
		uint32_t A;
		uint32_t B;
		uint32_t C;
		uint32_t D;

		constexpr FGuid() :
			FGuid(0, 0, 0, 0)
		{

		}

		constexpr FGuid(uint32_t A, uint32_t B, uint32_t C, uint32_t D) :
			A(A), B(B), C(C), D(D)
		{

		}

		friend FArchive& operator>>(FArchive& Ar, FGuid& Value) {
			Ar >> Value.A;
			Ar >> Value.B;
			Ar >> Value.C;
			Ar >> Value.D;

			return Ar;
		}
		
		void Invalidate() {
			A = 0;
			B = 0;
			C = 0;
			D = 0;
		}
	};
}