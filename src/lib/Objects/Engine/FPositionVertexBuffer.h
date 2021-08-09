#pragma once

#include "../Core/Math/FVector.h"
#include "../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FPositionVertexBuffer {
        uint32_t Stride;
        uint32_t NumVertices;
        std::vector<FVector> VertexData;

        friend FArchive& operator>>(FArchive& Ar, FPositionVertexBuffer& Value);
    };
}