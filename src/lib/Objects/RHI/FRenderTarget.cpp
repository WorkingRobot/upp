#include "FRenderTarget.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FRenderTarget& Value)
    {
        Ar >> Value.ColorBlendOp;
        Ar >> Value.ColorSrcBlend;
        Ar >> Value.ColorDestBlend;
        Ar >> Value.AlphaBlendOp;
        Ar >> Value.AlphaSrcBlend;
        Ar >> Value.AlphaDestBlend;
        Ar >> Value.ColorWriteMask;

        return Ar;
    }
}