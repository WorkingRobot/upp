#pragma once

#include "../Core/Serialization/FArchive.h"
#include "FRenderTarget.h"

namespace upp::Objects {
    struct FBlendStateInitializerRHI {
        static constexpr uint8_t MaxSimultaneousRenderTargets = 8;

        FRenderTarget RenderTargets[MaxSimultaneousRenderTargets];
        bool UseIndependentRenderTargetBlendStates;
        bool UseAlphaToCoverage;

        friend FArchive& operator>>(FArchive& Ar, FBlendStateInitializerRHI& Value);
    };
}