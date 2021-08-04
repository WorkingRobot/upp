#include "FStreamedAudioChunk.h"

namespace upp::Objects {
    void FStreamedAudioChunk::Serialize(FArchive& Ar, FSerializeCtx& Ctx)
    {
		int IsCooked;
		Ar >> IsCooked;

		BulkData.Serialize(Ar, Ctx);
		Ar >> DataSize;
		Ar >> AudioDataSize;
    }
}