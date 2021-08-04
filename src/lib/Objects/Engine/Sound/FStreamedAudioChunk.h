#pragma once

#include "../../CoreUObject/Serialization/FByteBulkData.h"
#include "../../CoreUObject/UObject/FSerializeCtx.h"

namespace upp::Objects {
    struct FStreamedAudioChunk {
        int DataSize;
        int AudioDataSize;
        FByteBulkData BulkData;

        void Serialize(FArchive& Ar, FSerializeCtx& Ctx);
    };
}