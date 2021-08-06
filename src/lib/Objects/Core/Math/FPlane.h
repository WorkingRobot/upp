#pragma once

#include "../Serialization/FArchive.h"
#include "FVector.h"

namespace upp::Objects {
	struct FPlane : public FVector {
        float W;

        friend FArchive& operator>>(FArchive& Ar, FPlane& Value);
	};
}