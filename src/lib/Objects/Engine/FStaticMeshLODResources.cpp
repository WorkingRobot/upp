#include "FStaticMeshLODResources.h"

#include "../CoreUObject/Serialization/FByteBulkData.h"
#include "FStaticMeshBuffersSize.h"
#include "FStripDataFlags.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/048ce1606af8daff143a1e99255aca9c6f04d46c/Engine/Source/Runtime/Engine/Private/StaticMesh.cpp#L657
    void FStaticMeshLODResources::Serialize(FArchive& Ar, FSerializeCtx& Ctx)
    {
        FStripDataFlags StripFlags;
        Ar >> StripFlags;

        Ar >> Sections;
        Ar >> MaxDeviation;

        int bIsLODCookedOut;
        Ar >> bIsLODCookedOut;
        IsLODCookedOut = bIsLODCookedOut;
        int bBuffersInlined;
        Ar >> bBuffersInlined;
        BuffersInlined = bBuffersInlined;

        if (!StripFlags.IsDataStrippedForServer() && !IsLODCookedOut) {
            FStaticMeshBuffersSize TmpBuffersSize;

            if (BuffersInlined) {
                SerializeBuffers(Ar);

                Ar >> TmpBuffersSize;
            }
            else {
                FByteBulkData TmpBulkData;
                TmpBulkData.Serialize(Ar, Ctx);

                auto BulkArchive = TmpBulkData.GetArchive();
                SerializeBuffers(BulkArchive);

                // SerializeAvailabilityInfo(Ar);
                // https://github.com/EpicGames/UnrealEngine/blob/d2acf8eff721d88a654648c6ac1c43137ae4dc23/Engine/Source/Runtime/Engine/Private/StaticMesh.cpp#L556
                Ar.Seek(  4 * 1 // DepthOnlyNumTriangles
                        + 4 * 1 // Packed
                        + 4 * 4 // StaticMeshVertexBuffer metadata
                        + 4 * 2 // PositionVertexBuffer metadata
                        + 4 * 2 // ColorVertexBuffer metadata
                        + 4 * 2 // IndexBuffer metadata
                        + 4 * 2 // ReversedIndexBuffer metadata
                        + 4 * 2 // DepthOnlyIndexBuffer metadata
                        + 4 * 2 // ReversedDepthOnlyIndexBuffer metadata
                        + 4 * 2 // WireframeIndexBuffer metadata
                        + 4 * 2 // AdjacencyIndexBuffer metadata
                    , ESeekDir::Cur);

                Ar >> TmpBuffersSize;
            }
        }
    }

    // https://github.com/EpicGames/UnrealEngine/blob/048ce1606af8daff143a1e99255aca9c6f04d46c/Engine/Source/Runtime/Engine/Private/StaticMesh.cpp#L462
    void FStaticMeshLODResources::SerializeBuffers(FArchive& Ar)
    {
        constexpr uint8_t CDSF_AdjacencyData = 1;
        constexpr uint8_t CDSF_MinLodData = 2;
        constexpr uint8_t CDSF_ReversedIndexBuffer = 4;
        constexpr uint8_t CDSF_RayTracingResources = 8;

        FStripDataFlags StripFlags;
        Ar >> StripFlags;

        Ar >> VertexBuffers.PositionVertexBuffer;
        Ar >> VertexBuffers.StaticMeshVertexBuffer;
        Ar >> VertexBuffers.ColorVertexBuffer;

        Ar >> IndexBuffer;

        if (!StripFlags.IsClassDataStripped(CDSF_ReversedIndexBuffer)) {
            Ar >> SerializedAdditionalIndexBuffers.ReversedIndexBuffer;
        }

        Ar >> DepthOnlyIndexBuffer;

        if (!StripFlags.IsClassDataStripped(CDSF_ReversedIndexBuffer)) {
            Ar >> SerializedAdditionalIndexBuffers.ReversedDepthOnlyIndexBuffer;
        }

        if (!StripFlags.IsEditorDataStripped()) {
            Ar >> SerializedAdditionalIndexBuffers.WireframeIndexBuffer;
        }

        if (!StripFlags.IsClassDataStripped(CDSF_AdjacencyData)) {
            Ar >> SerializedAdditionalIndexBuffers.AdjacencyIndexBuffer;
        }

        if (!StripFlags.IsClassDataStripped(CDSF_RayTracingResources)) {
            Ar.BulkSerialize(RayTracingGeometry);
        }

        AreaWeightedSectionSamplers.reserve(Sections.size());
        for (int Idx = 0; Idx < Sections.size(); ++Idx) {
            Ar >> AreaWeightedSectionSamplers.emplace_back();
        }
        Ar >> AreaWeightedSampler;
    }
}