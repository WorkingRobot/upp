#pragma once

#include "../Core/Serialization/FArchive.h"
#include "ERasterizerCullMode.h"
#include "ERasterizerFillMode.h"

namespace upp::Objects {
    struct FPipelineFileCacheRasterizerState {
        float DepthBias;
        float SlopeScaleDepthBias;
        ERasterizerFillMode FillMode;
        ERasterizerCullMode CullMode;
        bool AllowMSAA;
        bool EnableLineAA;

        friend FArchive& operator>>(FArchive& Ar, FPipelineFileCacheRasterizerState& Value);
    };
}