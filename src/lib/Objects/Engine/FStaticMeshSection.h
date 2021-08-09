#pragma once

#include "../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FStaticMeshSection {
        int MaterialIndex;
        uint32_t FirstIndex;
        uint32_t NumTriangles;
        uint32_t MinVertexIndex;
        uint32_t MaxVertexIndex;
        bool EnableCollision;
        bool CastShadow;
        bool ForceOpaque;
        bool VisibleInRayTracing;

        friend FArchive& operator>>(FArchive& Ar, FStaticMeshSection& Value);
    };
}