#pragma once

#include "../Serialization/FArchive.h"
#include "FFloat16.h"

namespace upp::Objects {
	struct FVector2DHalf {
        FFloat16 X, Y;

        friend FArchive& operator>>(FArchive& Ar, FVector2DHalf& Value);
	};
}