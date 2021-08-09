#pragma once

#include "../../Core/Math/FBoxSphereBounds.h"
#include "../../CoreUObject/UObject/UObject.h"
#include "../FBspNode.h"
#include "../FBspSurf.h"
#include "../FModelVertexBuffer.h"
#include "FVert.h"
#include "FLightmassPrimitiveSettings.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/bccdec1d349b12e817b8d565884044ce6365a619/Engine/Source/Runtime/Engine/Public/Model.h#L388
    struct UModel : public UObject {
        FBoxSphereBounds Bounds;
        std::vector<FVector> Vectors;
        std::vector<FVector> Points;
        std::vector<FBspNode> Nodes;
        std::vector<FBspSurf> Surfs;
        std::vector<FVert> Verts;
        int NumSharedSides;
        bool RootOutside;
        bool Linked;
        uint32_t NumUniqueVertices;
        FModelVertexBuffer VertexBuffer;
        FGuid LightingGuid;
        std::vector<FLightmassPrimitiveSettings> LightmassSettings;

        UModel(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO);
    };
}