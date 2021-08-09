#pragma once

#include "../Core/Math/FBoxSphereBounds.h"
#include "../Core/Serialization/FArchive.h"
#include "../CoreUObject/UObject/FSerializeCtx.h"
#include "TPerPlatformProperty.h"
#include "FStaticMeshLODResources.h"

namespace upp::Objects {
    struct FStaticMeshRenderData {
        static constexpr int MAX_STATIC_MESH_LODS = 8;

        std::vector<FStaticMeshLODResources> LODResources;
        uint8_t NumInlinedLODs;
        FBoxSphereBounds Bounds;
        bool LODsShareStaticLighting;
        FPerPlatformFloat ScreenSize[MAX_STATIC_MESH_LODS];

        void Serialize(FArchive& Ar, FSerializeCtx& Ctx);
    };
}