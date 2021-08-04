#include "FStreamedAudioPlatformData.h"

namespace upp::Objects {
    void FStreamedAudioPlatformData::Serialize(FArchive& Ar, FSerializeCtx& Ctx)
    {
		Ar >> NumChunks;
		Ar >> AudioFormat;

		Chunks.reserve(NumChunks);
		for (int Idx = 0; Idx < NumChunks; ++Idx) {
			Chunks.emplace_back().Serialize(Ar, Ctx);
		}
    }
}