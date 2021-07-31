#pragma once

#include "../Serialization/FArchive.h"

namespace upp::Objects {
	struct FLinearColor {
        float R, G, B, A;

        friend FArchive& operator>>(FArchive& Ar, FLinearColor& Value);
	};
}