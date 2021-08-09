#pragma once

#include "../Serialization/FArchive.h"

namespace upp::Objects {
	struct FIntVector {
        int X, Y, Z;

        friend FArchive& operator>>(FArchive& Ar, FIntVector& Value);
	};
}