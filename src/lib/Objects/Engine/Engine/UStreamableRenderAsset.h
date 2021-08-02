#pragma once

#include "../../CoreUObject/UObject/UObject.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/abee2073faa072b43e7ddb4dfe56299841cf9e42/Engine/Source/Runtime/Engine/Classes/Engine/StreamableRenderAsset.h#L30
    struct UStreamableRenderAsset : public UObject {
        UStreamableRenderAsset(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO) : UObject(Ar, Schema, Ctx, IsCDO) { }
    };
}