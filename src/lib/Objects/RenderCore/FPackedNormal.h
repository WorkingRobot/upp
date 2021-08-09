#pragma once

#include "../Core/Serialization/FArchive.h"

namespace upp::Objects {
	struct FPackedNormal {
        union {
            struct {
                int8_t X, Y, Z, W;
            };
            uint32_t Packed;
        };

        friend FArchive& operator>>(FArchive& Ar, FPackedNormal& Value);
	};
}