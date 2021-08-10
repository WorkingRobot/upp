#pragma once

#include "../Serialization/FArchive.h"

namespace upp::Objects {
	struct FQuat {
        float X, Y, Z, W;

        friend FArchive& operator>>(FArchive& Ar, FQuat& Value);
	};
}