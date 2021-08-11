#include "USkeletalMesh.h"

#include "../FStripDataFlags.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/adb0f8832c780488c0e4298a6af161881f95e33d/Engine/Source/Runtime/Engine/Private/SkeletalMesh.cpp#L1483
    USkeletalMesh::USkeletalMesh(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO) :
        UStreamableRenderAsset(Ar, Schema, Ctx, IsCDO)
    {
        bool HasVertexColors = false;
        auto HasVertexColorsProp = Get<bool>("bHasVertexColors");
        if (HasVertexColorsProp) {
            HasVertexColors = *HasVertexColorsProp;
        }

        FStripDataFlags StripFlags;
        Ar >> StripFlags;

        Ar >> ImportedBounds;

        Ar >> Materials;

        Ar >> RefSkeleton;

        int bCooked;
        Ar >> bCooked;

        if (bCooked) {
            SkeletalMeshRenderData.Serialize(Ar, Ctx, HasVertexColors);
        }

        std::vector<FPackageIndex> DummyObjs;
        Ar >> DummyObjs;
    }
}