#pragma once

#include "../Serialization/FArchive.h"

namespace upp::Objects {
	struct FRotator {
        float Pitch, Yaw, Roll;

        friend FArchive& operator>>(FArchive& Ar, FRotator& Value);
	};
}