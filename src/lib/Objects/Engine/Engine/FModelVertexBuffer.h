#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "FModelVertex.h"

namespace upp::Objects {
    struct FModelVertexBuffer {
        std::vector<FModelVertex> Vertices;

        friend FArchive& operator>>(FArchive& Ar, FModelVertexBuffer& Value);
    };
}