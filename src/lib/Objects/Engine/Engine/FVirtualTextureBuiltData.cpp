#include "FVirtualTextureBuiltData.h"

namespace upp::Objects {
    void FVirtualTextureBuiltData::Serialize(FArchive& Ar, FSerializeCtx& Ctx)
    {
        int IsCooked;
        Ar >> IsCooked;

        Ar >> NumLayers;
        Ar >> WidthInBlocks;
        Ar >> HeightInBlocks;
        Ar >> TileSize;
        Ar >> TileBorderSize;

        Ar >> NumMips;
        Ar >> Width;
        Ar >> Height;
        Ar >> TileIndexPerChunk;
        Ar >> TileIndexPerMip;
        Ar >> TileOffsetInChunk;

        {
            std::string PixelFormatName;
            for (int i = 0; i < NumLayers; ++i) {
                Ar >> PixelFormatName;
                LayerTypes.emplace_back(GetPixelFormat(PixelFormatName));
            }
        }

        {
            int SerializeNum;
            Ar >> SerializeNum;
            Chunks.reserve(SerializeNum);
            for (int i = 0; i < SerializeNum; ++i) {
                Chunks.emplace_back().Serialize(Ar, Ctx, NumLayers);
            }
        }
    }
}