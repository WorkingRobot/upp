#pragma once

#include "../Core/Serialization/FArchive.h"
#include "EShaderPlatform.h"
#include "FPipelineCacheFileFormatTOC.h"
#include "FPipelineCacheFileFormatPSO.h"

namespace upp::Objects {
    struct FPipelineFileCache {
        uint32_t GameVersion;
        EShaderPlatform ShaderPlatform;
        FPipelineCacheFileFormatTOC TOC;
        FGuid FileGuid;
        std::vector<FPipelineCacheFileFormatPSO> Entries;

        FPipelineFileCache(FArchive& Ar);
        friend FArchive& operator>>(FArchive& Ar, FPipelineFileCache& Value);
    };
}