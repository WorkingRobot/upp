#pragma once

#include "../../Core/Math/FBoxSphereBounds.h"
#include "../Rendering/FSkeletalMeshRenderData.h"
#include "../FReferenceSkeleton.h"
#include "FSkeletalMaterial.h"
#include "UStreamableRenderAsset.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/adb0f8832c780488c0e4298a6af161881f95e33d/Engine/Source/Runtime/Engine/Classes/Engine/SkeletalMesh.h#L507
    struct USkeletalMesh : public UStreamableRenderAsset {
        FBoxSphereBounds ImportedBounds;
        std::vector<FSkeletalMaterial> Materials;
        FReferenceSkeleton RefSkeleton;
        FSkeletalMeshRenderData SkeletalMeshRenderData;

        USkeletalMesh(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO);
    };
}