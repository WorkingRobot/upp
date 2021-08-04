#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "FByteBulkData.h"

namespace upp::Objects {
    struct FFormatContainer {
        std::vector<std::pair<FName, FByteBulkData>> Formats;

        void Serialize(FArchive& Ar, FSerializeCtx& Ctx);
    };
}