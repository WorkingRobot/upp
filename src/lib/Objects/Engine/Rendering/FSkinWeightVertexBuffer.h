#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "FSkinWeightDataVertexBuffer.h"
#include "FSkinWeightLookupVertexBuffer.h"

namespace upp::Objects {
    struct FSkinWeightVertexBuffer {
        FSkinWeightDataVertexBuffer DataVertexBuffer;
        FSkinWeightLookupVertexBuffer LookupVertexBuffer;

        friend FArchive& operator>>(FArchive& Ar, FSkinWeightVertexBuffer& Value);
    };
}