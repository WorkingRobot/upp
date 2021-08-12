#pragma once

#include "../Serialization/FArchive.h"
#include "FVector2D.h"

namespace upp::Objects {
	struct FBox2D {
        FVector2D Min;
        FVector2D Max;
        uint8_t IsValid;

        friend FArchive& operator>>(FArchive& Ar, FBox2D& Value);
	};
}