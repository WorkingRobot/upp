#pragma once

#include "../Core/Serialization/FArchive.h"
#include "EBlendFactor.h"
#include "EBlendOperation.h"
#include "EColorWriteMask.h"

namespace upp::Objects {
    struct FRenderTarget {
        EBlendOperation ColorBlendOp;
        EBlendFactor ColorSrcBlend;
        EBlendFactor ColorDestBlend;
        EBlendOperation AlphaBlendOp;
        EBlendFactor AlphaSrcBlend;
        EBlendFactor AlphaDestBlend;
        EColorWriteMask ColorWriteMask;

        friend FArchive& operator>>(FArchive& Ar, FRenderTarget& Value);
    };
}