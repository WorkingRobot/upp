#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "../../CoreUObject/UObject/FSerializeCtx.h"
#include "FSkeletalMeshLODRenderData.h"

namespace upp::Objects {
    struct FSkeletalMeshRenderData {
        std::vector<FSkeletalMeshLODRenderData> LODRenderData;
        uint8_t NumInlinedLODs;
        uint8_t NumNonOptionalLODs;

        void Serialize(FArchive& Ar, FSerializeCtx& Ctx, bool HasVertexColors);
    };
}