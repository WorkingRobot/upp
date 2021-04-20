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

		constexpr FGuid(uint32_t Val) :
			FGuid(Val, Val, Val, Val)
		{

		}

		friend FArchive& operator>>(FArchive& Ar, FGuid& Value) {
			Ar >> Value.A;
			Ar >> Value.B;
			Ar >> Value.C;
			Ar >> Value.D;

			return Ar;
		}

		constexpr bool IsValid() const {
			return FGuid() != *this;
		}
		
		void Invalidate() {
			*this = FGuid();
		}

		friend auto operator<=>(const FGuid&, const FGuid&) = default;
	};
}