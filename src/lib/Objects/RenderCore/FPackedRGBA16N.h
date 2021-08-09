#pragma once

#include "../Core/Serialization/FArchive.h"

namespace upp::Objects {
	struct FPackedRGBA16N {
        int16_t X, Y, Z, W;

        friend FArchive& operator>>(FArchive& Ar, FPackedRGBA16N& Value);
	};
}