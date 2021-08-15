#pragma once

#include "../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FPipelineStateStats {
        int64_t FirstFrameUsed;
        int64_t LastFrameUsed;
        uint64_t CreateCount;
        int64_t TotalBindCount;
        uint32_t PSOHash;

        friend FArchive& operator>>(FArchive& Ar, FPipelineStateStats& Value);
    };
}