#pragma once

#include "../Core/Serialization/FArchive.h"
#include "EPSODescriptorType.h"
#include "FPSODescriptor.h"

#include <variant>

namespace upp::Objects {
    struct FPipelineCacheFileFormatPSO {
        std::variant<FPSOComputeDescriptor, FPSOGraphicsDescriptor, FPSORaytracingDescriptor> Data;

        friend FArchive& operator>>(FArchive& Ar, FPipelineCacheFileFormatPSO& Value);
    };
}