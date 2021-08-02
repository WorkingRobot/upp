#include "UTexture.h"

#include "../FStripDataFlags.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/abee2073faa072b43e7ddb4dfe56299841cf9e42/Engine/Source/Runtime/Engine/Private/Texture.cpp#L413
    UTexture::UTexture(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO) :
        UStreamableRenderAsset(Ar, Schema, Ctx, IsCDO)
    {
        FStripDataFlags StripFlags;
        Ar >> StripFlags;
    }
}