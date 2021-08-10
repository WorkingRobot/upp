#pragma once

#include "../Serialization/FArchive.h"
#include "FQuat.h"
#include "FVector.h"

namespace upp::Objects {
	struct FTransform {
        FQuat Rotation;
        FVector Translation;
        FVector Scale3D;

        friend FArchive& operator>>(FArchive& Ar, FTransform& Value);
	};
}