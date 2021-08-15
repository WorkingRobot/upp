#pragma once

#include "../Core/Misc/FGuid.h"
#include "../Core/Serialization/FArchive.h"
#include "EPipelineCacheFileFormatVersions.h"
#include "EShaderPlatform.h"

namespace upp::Objects {
    struct FPipelineCacheFileFormatHeader {
        uint64_t Magic;
        EPipelineCacheFileFormatVersions Version;
        uint32_t GameVersion;
        EShaderPlatform Platform;
        FGuid Guid;
        uint64_t TableOffset;

        friend FArchive& operator>>(FArchive& Ar, FPipelineCacheFileFormatHeader& Value);
    };
}