#pragma once

#include "../Serialization/FArchive.h"

namespace upp::Objects {
	struct FVector {
        float X, Y, Z;

        friend FArchive& operator>>(FArchive& Ar, FVector& Value);
	};
}