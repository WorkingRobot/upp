#include "FPipelineCacheFileFormatPSO.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FPipelineCacheFileFormatPSO& Value)
    {
        EPSODescriptorType Type;
        Ar >> Type;

        switch (Type)
        {
        case EPSODescriptorType::Compute:
            return Ar >> Value.Data.emplace<FPSOComputeDescriptor>();
        case EPSODescriptorType::Graphics:
            return Ar >> Value.Data.emplace<FPSOGraphicsDescriptor>();
        case EPSODescriptorType::RayTracing:
            return Ar >> Value.Data.emplace<FPSORaytracingDescriptor>();
        default:
            return Ar;
        }
    }
}