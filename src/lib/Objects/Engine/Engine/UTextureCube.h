#pragma once

#include "UTexture2D.h"

namespace upp::Objects {
    struct UTextureCube : public UTexture2D {
        // Identical serializer to UTexture2D: https://github.com/EpicGames/UnrealEngine/blob/65cbeac6d1bdefdf560f3f879db3f599cf166a3c/Engine/Source/Runtime/Engine/Private/TextureCube.cpp#L23
        UTextureCube(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO) : UTexture2D(Ar, Schema, Ctx, IsCDO) { }
    };
}