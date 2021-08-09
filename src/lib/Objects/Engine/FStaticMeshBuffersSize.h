#pragma once

#include "../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FStaticMeshBuffersSize {
        uint32_t SerializedBuffersSize;
        uint32_t DepthOnlyIBSize;
        uint32_t ReversedIBsSize;

        friend FArchive& operator>>(FArchive& Ar, FStaticMeshBuffersSize& Value);
    };
}