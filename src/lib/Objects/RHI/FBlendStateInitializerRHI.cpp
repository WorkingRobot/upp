#include "FBlendStateInitializerRHI.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FBlendStateInitializerRHI& Value)
    {
        Ar >> Value.RenderTargets;

        int bUseIndependentRenderTargetBlendStates;
        Ar >> bUseIndependentRenderTargetBlendStates;
        Value.UseIndependentRenderTargetBlendStates = bUseIndependentRenderTargetBlendStates;

        int bUseAlphaToCoverage;
        Ar >> bUseAlphaToCoverage;
        Value.UseAlphaToCoverage = bUseAlphaToCoverage;

        return Ar;
    }
}