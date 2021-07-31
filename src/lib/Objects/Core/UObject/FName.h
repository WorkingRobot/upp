#pragma once

#include "../Serialization/FArchive.h"

namespace upp::Objects {
	struct FName {
        FName(uint32_t Index = 0, uint32_t Number = 0);

        uint32_t Index;
        uint32_t Number;

        friend FArchive& operator>>(FArchive& Ar, FName& Value);
	};
}