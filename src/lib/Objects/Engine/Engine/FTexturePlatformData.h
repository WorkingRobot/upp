#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "../../Core/EPixelFormat.h"
#include "../../CoreUObject/UObject/FSerializeCtx.h"
#include "../FTexture2DMipMap.h"
#include "FVirtualTextureBuiltData.h"

namespace upp::Objects {
    struct FTexturePlatformData {
        int SizeX;
        int SizeY;
        uint32_t PackedData;
        EPixelFormat PixelFormat;
        std::vector<FTexture2DMipMap> Mips;
        std::optional<FVirtualTextureBuiltData> VTData;

        void Serialize(FArchive& Ar, FSerializeCtx& Ctx);
    };
}