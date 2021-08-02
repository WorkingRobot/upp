#pragma once

#include "FTexturePlatformData.h"
#include "UTexture.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/abee2073faa072b43e7ddb4dfe56299841cf9e42/Engine/Source/Runtime/Engine/Classes/Engine/Texture.h#L615
    struct UTexture2D : public UTexture {
        FTexturePlatformData PlatformData;

        UTexture2D(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO);
    };
}