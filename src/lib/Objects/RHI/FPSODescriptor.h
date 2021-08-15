#pragma once

#include "../Core/Misc/FSHAHash.h"
#include "../Core/Serialization/FArchive.h"
#include "../Core/EPixelFormat.h"
#include "EPrimitiveType.h"
#include "EPSODescriptorType.h"
#include "ERenderTargetLoadAction.h"
#include "ERenderTargetStoreAction.h"
#include "EShaderFrequency.h"
#include "ETextureCreateFlags.h"
#include "FBlendStateInitializerRHI.h"
#include "FDepthStencilStateInitializerRHI.h"
#include "FPipelineFileCacheRasterizerState.h"
#include "FVertexDeclarationElementList.h"

namespace upp::Objects {
    template<EPSODescriptorType Type>
    struct FPSODescriptor;
    
    using FPSOComputeDescriptor = FPSODescriptor<EPSODescriptorType::Compute>;
    using FPSOGraphicsDescriptor = FPSODescriptor<EPSODescriptorType::Graphics>;
    using FPSORaytracingDescriptor = FPSODescriptor<EPSODescriptorType::RayTracing>;

    template<>
    struct FPSODescriptor<EPSODescriptorType::Compute> {
        FSHAHash ComputeShader;

        friend FArchive& operator>>(FArchive& Ar, FPSOComputeDescriptor& Value);
    };

    template<>
    struct FPSODescriptor<EPSODescriptorType::Graphics> {
        FSHAHash VertexShader;
        FSHAHash FragmentShader;
        FSHAHash GeometryShader;
        FSHAHash HullShader;
        FSHAHash DomainShader;
        FSHAHash MeshShader;
        FSHAHash AmplificationShader;

        FVertexDeclarationElementList VertexDescriptor;
        FBlendStateInitializerRHI BlendState;
        FPipelineFileCacheRasterizerState RasterizerState;
        FDepthStencilStateInitializerRHI DepthStencilState;

        EPixelFormat RenderTargetFormats[FBlendStateInitializerRHI::MaxSimultaneousRenderTargets];
        ETextureCreateFlags RenderTargetFlags[FBlendStateInitializerRHI::MaxSimultaneousRenderTargets];
        uint32_t RenderTargetsActive;
        uint32_t MSAASamples;

        EPixelFormat DepthStencilFormat;
        uint32_t DepthStencilFlags;
        ERenderTargetLoadAction DepthLoad;
        ERenderTargetLoadAction StencilLoad;
        ERenderTargetStoreAction DepthStore;
        ERenderTargetStoreAction StencilStore;

        EPrimitiveType PrimitiveType;

        uint8_t SubpassHint;
        uint8_t SubpassIndex;

        friend FArchive& operator>>(FArchive& Ar, FPSOGraphicsDescriptor& Value);
    };

    template<>
    struct FPSODescriptor<EPSODescriptorType::RayTracing> {
        FSHAHash ShaderHash;
        uint32_t MaxPayloadSizeInBytes;
        EShaderFrequency Frequency;
        bool AllowHitGroupIndexing;

        friend FArchive& operator>>(FArchive& Ar, FPSORaytracingDescriptor& Value);
    };
}