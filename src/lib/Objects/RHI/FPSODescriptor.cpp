#include "FPSODescriptor.h"

#include "EPipelineCacheFileFormatVersions.h"
#include "EShaderFrequency.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FPSOComputeDescriptor& Value)
    {
        Ar >> Value.ComputeShader;
        if constexpr (EPipelineCacheFileFormatVersions::Supported == EPipelineCacheFileFormatVersions::LibraryID) {
            uint32_t ID;
            Ar >> ID;
        }

        return Ar;
    }

    FArchive& operator>>(FArchive& Ar, FPSOGraphicsDescriptor& Value)
    {
        Ar >> Value.VertexShader;
        Ar >> Value.FragmentShader;
        Ar >> Value.GeometryShader;
        Ar >> Value.HullShader;
        Ar >> Value.DomainShader;
        if constexpr (EPipelineCacheFileFormatVersions::Supported >= EPipelineCacheFileFormatVersions::AddingMeshShaders) {
            //Ar >> Value.MeshShader;
            //Ar >> Value.AmplificationShader;
        }
        if constexpr (EPipelineCacheFileFormatVersions::Supported == EPipelineCacheFileFormatVersions::LibraryID) {
            for (uint32_t Idx = 0; Idx < (uint32_t)EShaderFrequency::SF_Compute; ++Idx) {
                uint32_t ID;
                Ar >> ID;
            }
        }
        Ar >> Value.VertexDescriptor;
        if constexpr (EPipelineCacheFileFormatVersions::Supported < EPipelineCacheFileFormatVersions::SortedVertexDesc) {
            std::sort(Value.VertexDescriptor.begin(), Value.VertexDescriptor.end());
        }
        Ar >> Value.BlendState;
        Ar >> Value.RasterizerState;
        Ar >> Value.DepthStencilState;
        for (uint32_t Idx = 0; Idx < FBlendStateInitializerRHI::MaxSimultaneousRenderTargets; ++Idx)
        {
            Ar >> Value.RenderTargetFormats[Idx];
            Ar >> Value.RenderTargetFlags[Idx];
            uint8_t LoadStore;
            Ar >> LoadStore >> LoadStore;
        }
        Ar >> Value.RenderTargetsActive;
        Ar >> Value.MSAASamples;
        Ar >> Value.PrimitiveType;
        Ar >> Value.DepthStencilFormat;
        Ar >> Value.DepthStencilFlags;
        Ar >> Value.DepthLoad;
        Ar >> Value.StencilLoad;
        Ar >> Value.DepthStore;
        Ar >> Value.StencilStore;

        Ar >> Value.SubpassHint;
        Ar >> Value.SubpassIndex;

        return Ar;
    }

    FArchive& operator>>(FArchive& Ar, FPSORaytracingDescriptor& Value)
    {
        Ar >> Value.ShaderHash;
        Ar >> Value.MaxPayloadSizeInBytes;
        uint32_t Frequency;
        Ar >> Frequency;
        Value.Frequency = (EShaderFrequency)Frequency;
        int bAllowHitGroupIndexing;
        Ar >> bAllowHitGroupIndexing;
        Value.AllowHitGroupIndexing = bAllowHitGroupIndexing;

        return Ar;
    }
}