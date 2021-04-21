#pragma once

#include "../Serialization/FArchive.h"

namespace upp::Objects {
	struct FSerializedNameHeader {
    public:
        bool IsUtf16() const {
            return Data[0] & 0x80;
        }

        uint16_t Len() const {
            return ((Data[0] & 0x7Fu) << 8) + Data[1];
        }

        friend FArchive& operator>>(FArchive& Ar, FSerializedNameHeader& Value);

    private:
        uint8_t Data[2];
	};
}