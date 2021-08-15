#pragma once

#include "../Core/Serialization/FArchive.h"
#include "ECompareFunction.h"
#include "EStencilOp.h"

namespace upp::Objects {
    struct FDepthStencilStateInitializerRHI {
        bool EnableDepthWrite;
        ECompareFunction DepthTest;

        bool EnableFrontFaceStencil;
        ECompareFunction FrontFaceStencilTest;
        EStencilOp FrontFaceStencilFailStencilOp;
        EStencilOp FrontFaceDepthFailStencilOp;
        EStencilOp FrontFacePassStencilOp;
        bool EnableBackFaceStencil;
        ECompareFunction BackFaceStencilTest;
        EStencilOp BackFaceStencilFailStencilOp;
        EStencilOp BackFaceDepthFailStencilOp;
        EStencilOp BackFacePassStencilOp;
        uint8_t StencilReadMask;
        uint8_t StencilWriteMask;

        friend FArchive& operator>>(FArchive& Ar, FDepthStencilStateInitializerRHI& Value);
    };
}