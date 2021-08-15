#pragma once

#include <stdint.h>

namespace upp::Objects {
    // Internally FPipelineCacheFileFormatPSO::DescriptorType, but I moved it out to here
    enum class EPSODescriptorType : uint32_t {
        Compute = 0,
        Graphics = 1,
        RayTracing = 2,
    };
}