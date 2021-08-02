#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "../../Core/EPixelFormat.h"
#include "../../CoreUObject/UObject/FSerializeCtx.h"
#include "../FTexture2DMipMap.h"
#include "FVirtualTextureDataChunk.h"

namespace upp::Objects {
    struct FVirtualTextureBuiltData {
        uint32_t NumLayers;
        uint32_t WidthInBlocks;
        uint32_t HeightInBlocks;
        uint32_t TileSize;
        uint32_t TileBorderSize;

        uint32_t NumMips;
        uint32_t Width;
        uint32_t Height;
        std::vector<uint32_t> TileIndexPerChunk;
        std::vector<uint32_t> TileIndexPerMip;
        std::vector<uint32_t> TileOffsetInChunk;

        std::vector<EPixelFormat> LayerTypes;
        std::vector<FVirtualTextureDataChunk> Chunks;

        void Serialize(FArchive& Ar, FSerializeCtx& Ctx);
    };
}