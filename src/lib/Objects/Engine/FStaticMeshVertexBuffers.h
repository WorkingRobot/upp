#pragma once

#include "FColorVertexBuffer.h"
#include "FPositionVertexBuffer.h"
#include "FStaticMeshVertexBuffer.h"

namespace upp::Objects {
    struct FStaticMeshVertexBuffers {
        FStaticMeshVertexBuffer StaticMeshVertexBuffer;
        FPositionVertexBuffer PositionVertexBuffer;
        FColorVertexBuffer ColorVertexBuffer;
    };
}