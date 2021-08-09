#pragma once

#include "../Core/Serialization/FArchive.h"
#include "../CoreUObject/UObject/FSerializeCtx.h"
#include "FAdditionalStaticMeshIndexBuffers.h"
#include "FDistanceFieldVolumeData.h"
#include "FRawStaticIndexBuffer.h"
#include "FStaticMeshSection.h"
#include "FStaticMeshVertexBuffers.h"
#include "FWeightedRandomSampler.h"

namespace upp::Objects {
    struct FStaticMeshLODResources {
        std::vector<FStaticMeshSection> Sections;
        float MaxDeviation;
        bool IsLODCookedOut;
        bool BuffersInlined;
        FStaticMeshVertexBuffers VertexBuffers;
        FRawStaticIndexBuffer IndexBuffer;
        FRawStaticIndexBuffer DepthOnlyIndexBuffer;
        std::vector<uint8_t> RayTracingGeometry;
        FAdditionalStaticMeshIndexBuffers SerializedAdditionalIndexBuffers;
        FStaticMeshAreaWeightedSectionSampler AreaWeightedSampler;
        std::vector<FStaticMeshSectionAreaWeightedTriangleSampler> AreaWeightedSectionSamplers;
        FDistanceFieldVolumeData DistanceFieldData;

        void Serialize(FArchive& Ar, FSerializeCtx& Ctx);

    private:
        void SerializeBuffers(FArchive& Ar);
    };
}