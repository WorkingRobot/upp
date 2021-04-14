#pragma once

#include "../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FPakCompressedBlock {
        int64_t CompressedStart;

        int64_t CompressedEnd;

        friend FArchive& operator>>(FArchive& Ar, FPakCompressedBlock& Value);
    };
}