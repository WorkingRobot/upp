#pragma once

#include "../Serialization/FArchive.h"

namespace upp::Objects {
	struct FVector2D {
        float X, Y;

        friend FArchive& operator>>(FArchive& Ar, FVector2D& Value);
	};
}