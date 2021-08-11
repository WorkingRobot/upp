#pragma once

#include "../../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FSkinWeightLookupVertexBuffer {
        uint32_t NumVertices;
        std::vector<uint32_t> LookupData;

        friend FArchive& operator>>(FArchive& Ar, FSkinWeightLookupVertexBuffer& Value);
    };
}