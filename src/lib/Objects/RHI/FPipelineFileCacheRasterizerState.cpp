#include "FPipelineFileCacheRasterizerState.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FPipelineFileCacheRasterizerState& Value)
    {
        Ar >> Value.DepthBias;
        Ar >> Value.SlopeScaleDepthBias;
        Ar >> Value.FillMode;
        Ar >> Value.CullMode;

        int bAllowMSAA;
        Ar >> bAllowMSAA;
        Value.AllowMSAA = bAllowMSAA;

        int bEnableLineAA;
        Ar >> bEnableLineAA;
        Value.EnableLineAA = bEnableLineAA;

        return Ar;
    }
}