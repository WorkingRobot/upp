#pragma once

#include "../Serialization/FArchive.h"

namespace upp::Objects {
	struct FSerializedNameHeader {
        uint16_t Len;
        bool IsUtf16;

        friend FArchive& operator>>(FArchive& Ar, FSerializedNameHeader& Value);
	};
}