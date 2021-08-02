#include "FVirtualTextureDataChunk.h"

namespace upp::Objects {
    void FVirtualTextureDataChunk::Serialize(FArchive& Ar, FSerializeCtx& Ctx, uint32_t NumLayers)
    {
		Ar >> SizeInBytes;
		Ar >> CodecPayloadSize;

		CodecType.reserve(NumLayers);
		CodecPayloadOffset.reserve(NumLayers);
		for (int i = 0; i < NumLayers; ++i) {
			Ar >> CodecType.emplace_back();
			Ar >> CodecPayloadOffset.emplace_back();
		}

		BulkData.Serialize(Ar, Ctx);
    }
}