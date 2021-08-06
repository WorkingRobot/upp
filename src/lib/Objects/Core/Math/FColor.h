#pragma once

#include "../Serialization/FArchive.h"

namespace upp::Objects {
	struct FColor {
        uint8_t R, G, B, A;

        friend FArchive& operator>>(FArchive& Ar, FColor& Value);
	};
}