#pragma once

#include "../Serialization/FArchive.h"
#include "FVector.h"

namespace upp::Objects {
	struct FBox {
        FVector Min;
        FVector Max;
        uint8_t IsValid;

        friend FArchive& operator>>(FArchive& Ar, FBox& Value);
	};
}