#include "FDepthStencilStateInitializerRHI.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FDepthStencilStateInitializerRHI& Value)
    {
        int bEnableDepthWrite;
        Ar >> bEnableDepthWrite;
        Value.EnableDepthWrite = bEnableDepthWrite;
        Ar >> Value.DepthTest;

        int bEnableFrontFaceStencil;
        Ar >> bEnableFrontFaceStencil;
        Value.EnableFrontFaceStencil = bEnableFrontFaceStencil;
        Ar >> Value.FrontFaceStencilTest;
        Ar >> Value.FrontFaceStencilFailStencilOp;
        Ar >> Value.FrontFaceDepthFailStencilOp;
        Ar >> Value.FrontFacePassStencilOp;

        int bEnableBackFaceStencil;
        Ar >> bEnableBackFaceStencil;
        Value.EnableBackFaceStencil = bEnableBackFaceStencil;
        Ar >> Value.BackFaceStencilTest;
        Ar >> Value.BackFaceStencilFailStencilOp;
        Ar >> Value.BackFaceDepthFailStencilOp;
        Ar >> Value.BackFacePassStencilOp;

        Ar >> Value.StencilReadMask;
        Ar >> Value.StencilWriteMask;

        return Ar;
    }
}