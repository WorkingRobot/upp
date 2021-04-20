#pragma once

#include "../Serialization/FArchive.h"

namespace upp::Objects {
    struct FIoChunkId {
        char Id[12];

        friend FArchive& operator>>(FArchive& Ar, FIoChunkId& Value);

        friend auto operator<=>(const FIoChunkId&, const FIoChunkId&) = default;
    };
}