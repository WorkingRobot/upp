#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class EShaderFrequency : uint8_t {
        SF_Vertex = 0,
        SF_Hull = 1,
        SF_Domain = 2,
        SF_Pixel = 3,
        SF_Geometry = 4,
        SF_Compute = 5,
        SF_RayGen = 6,
        SF_RayMiss = 7,
        SF_RayHitGroup = 8,
        SF_RayCallable = 9,

        SF_NumFrequencies = 10,

        // Number of standard SM5-style shader frequencies for graphics pipeline (excluding compute)
        SF_NumGraphicsFrequencies = 5,

        // Number of standard SM5-style shader frequencies (including compute)
        SF_NumStandardFrequencies = 6,

        SF_NumBits = 4,
    };
}