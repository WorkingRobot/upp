#pragma once

#include "../Core/Math/FColor.h"
#include "../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FColorVertexBuffer {
        uint32_t Stride;
        uint32_t NumVertices;
        std::vector<FColor> VertexData;

        friend FArchive& operator>>(FArchive& Ar, FColorVertexBuffer& Value);
    };
}