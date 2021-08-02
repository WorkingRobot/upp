#pragma once

#include "../../CoreUObject/Serialization/FByteBulkData.h"
#include "../../CoreUObject/UObject/FSerializeCtx.h"
#include "EVirtualTextureCodec.h"

namespace upp::Objects {
    struct FVirtualTextureDataChunk {
        uint32_t SizeInBytes;
        uint32_t CodecPayloadSize;
        std::vector<EVirtualTextureCodec> CodecType;
        std::vector<uint16_t> CodecPayloadOffset;
        FByteBulkData BulkData;

        void Serialize(FArchive& Ar, FSerializeCtx& Ctx, uint32_t NumLayers);
    };
}