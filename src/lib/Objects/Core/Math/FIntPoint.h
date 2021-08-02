#pragma once

#include "../Serialization/FArchive.h"

namespace upp::Objects {
	struct FIntPoint {
        int X, Y;

        friend FArchive& operator>>(FArchive& Ar, FIntPoint& Value);
	};
}