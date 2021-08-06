#pragma once

#include "../Serialization/FArchive.h"
#include "FVector.h"

namespace upp::Objects {
	struct FBoxSphereBounds {
        FVector Origin;
        FVector BoxExtent;
        float SphereRadius;

        friend FArchive& operator>>(FArchive& Ar, FBoxSphereBounds& Value);
	};
}