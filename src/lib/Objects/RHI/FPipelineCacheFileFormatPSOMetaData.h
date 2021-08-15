#pragma once

#include "../Core/Misc/FGuid.h"
#include "../Core/Misc/FSHAHash.h"
#include "../Core/Serialization/FArchive.h"
#include "FPipelineStateStats.h"

namespace upp::Objects {
    struct FPipelineCacheFileFormatPSOMetaData {
        uint64_t FileOffset;
        uint64_t FileSize;
        FGuid FileGuid;
        FPipelineStateStats Stats;
        std::vector<FSHAHash> Shaders;
        uint64_t UsageMask;
        int64_t LastUsedUnixTime;
        uint16_t EngineFlags;

        friend FArchive& operator>>(FArchive& Ar, FPipelineCacheFileFormatPSOMetaData& Value);
    };
}