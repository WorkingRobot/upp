#pragma once

#include "../Core/Serialization/FArchive.h"
#include "EPSOOrder.h"
#include "FPipelineCacheFileFormatPSOMetaData.h"

namespace upp::Objects {
    struct FPipelineCacheFileFormatTOC {
        EPSOOrder SortedOrder;
        std::vector<std::pair<uint32_t, FPipelineCacheFileFormatPSOMetaData>> MetaData;

        friend FArchive& operator>>(FArchive& Ar, FPipelineCacheFileFormatTOC& Value);
    };
}