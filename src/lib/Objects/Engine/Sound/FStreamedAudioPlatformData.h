#pragma once

#include "../../CoreUObject/UObject/FSerializeCtx.h"
#include "FStreamedAudioChunk.h"

namespace upp::Objects {
    struct FStreamedAudioPlatformData {
        int NumChunks;
        FName AudioFormat;
        std::vector<FStreamedAudioChunk> Chunks;

        void Serialize(FArchive& Ar, FSerializeCtx& Ctx);
    };
}