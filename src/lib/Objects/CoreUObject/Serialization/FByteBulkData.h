#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "../../CoreUObject/UObject/FSerializeCtx.h"
#include "EBulkDataFlags.h"

namespace upp::Objects {
    struct FByteBulkData {
        int64_t BulkDataSize;
        int64_t BulkDataOffset;
        EBulkDataFlags BulkDataFlags;
        std::unique_ptr<char[]> Data;

        void Serialize(FArchive& Ar, FSerializeCtx& Ctx);
    };
}