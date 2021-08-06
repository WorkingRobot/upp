#pragma once

#include "../Serialization/FArchive.h"

namespace upp::Objects {
	struct FVector4 {
        float X, Y, Z, W;

        friend FArchive& operator>>(FArchive& Ar, FVector4& Value);
	};
}