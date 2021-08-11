#include "FSkeletalMeshLODRenderData.h"

#include "../../CoreUObject/Serialization/FByteBulkData.h"
#include "../FStripDataFlags.h"

namespace upp::Objects {
    constexpr uint8_t CDSF_AdjacencyData = 1;
    constexpr uint8_t CDSF_MinLodData = 2;

    void FSkeletalMeshLODRenderData::Serialize(FArchive& Ar, FSerializeCtx& Ctx, bool HasVertexColors)
    {
        FStripDataFlags StripFlags;
        Ar >> StripFlags;

        int bIsLODCookedOut;
        Ar >> bIsLODCookedOut;

        int bIsInlined;
        Ar >> bIsInlined;

        Ar >> RequiredBones;

        if (!StripFlags.IsDataStrippedForServer() && !bIsLODCookedOut) {
            Ar >> RenderSections;
            Ar >> ActiveBoneIndices;
            Ar >> BuffersSize;

            if (bIsInlined) {
                SerializeStreamedData(Ar, HasVertexColors);
            }
            else {
                FByteBulkData TmpBulkData;
                TmpBulkData.Serialize(Ar, Ctx);

                if (TmpBulkData.BulkDataSize > 0) {
                    auto BulkArchive = TmpBulkData.GetArchive();
                    SerializeStreamedData(BulkArchive, HasVertexColors);

                    // SerializeAvailabilityInfo(Ar, OwnerMesh, Idx, StripFlags.IsClassDataStripped(CDSF_AdjacencyData), bNeedsCPUAccess);
                    // https://github.com/EpicGames/UnrealEngine/blob/adb0f8832c780488c0e4298a6af161881f95e33d/Engine/Source/Runtime/Engine/Private/SkeletalMeshLODRenderData.cpp#L688
                    Ar.Seek(  1 + 4 // MultiSizeIndexContainer metadata
                            + (!StripFlags.IsClassDataStripped(CDSF_AdjacencyData) ? 1 + 4 : 0) // AdjacencyMultiSizeIndexContainer metadata
                            + 4 * 4 // StaticMeshVertexBuffer metadata
                            + 4 * 2 // PositionVertexBuffer metadata
                            + 4 * 2 // ColorVertexBuffer metadata
                            + 4 * 5 + 4 * 1 // SkinWeightVertexBuffer metadata
                        , ESeekDir::Cur);
                    // ClothVertexBuffer metadata
                    if (HasClothData()) {
                        std::vector<std::pair<uint32_t, uint32_t>> ClothIndexMapping;
                        Ar >> ClothIndexMapping;
                        Ar.Seek(4 * 2, ESeekDir::Cur);
                    }
                    // SkinWeightProfilesData metadata
                    {
                        std::vector<FName> OverrideData;
                        Ar >> OverrideData;
                    }
                }
            }
        }
    }

    // https://github.com/EpicGames/UnrealEngine/blob/adb0f8832c780488c0e4298a6af161881f95e33d/Engine/Source/Runtime/Engine/Private/SkeletalMeshLODRenderData.cpp#L909
    bool FSkeletalMeshLODRenderData::HasClothData() const
    {
        return std::any_of(RenderSections.begin(), RenderSections.end(), [](const FSkelMeshRenderSection& Section) {
            // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/Engine/Public/Rendering/SkeletalMeshLODRenderData.h#L85
            return !Section.ClothMappingData.empty();
        });
    }

    // https://github.com/EpicGames/UnrealEngine/blob/adb0f8832c780488c0e4298a6af161881f95e33d/Engine/Source/Runtime/Engine/Private/SkeletalMeshLODRenderData.cpp#L633
    void FSkeletalMeshLODRenderData::SerializeStreamedData(FArchive& Ar, bool HasVertexColors)
    {
        FStripDataFlags StripFlags;
        Ar >> StripFlags;

        Ar >> MultiSizeIndexContainer;

        Ar >> StaticVertexBuffers.PositionVertexBuffer;
        Ar >> StaticVertexBuffers.StaticMeshVertexBuffer;
        Ar >> SkinWeightVertexBuffer;

        if (HasVertexColors) {
            Ar >> StaticVertexBuffers.ColorVertexBuffer;
        }

        if (!StripFlags.IsClassDataStripped(CDSF_AdjacencyData)) {
            Ar >> AdjacencyMultiSizeIndexContainer;
        }

        if (HasClothData()) {
            Ar >> ClothVertexBuffer;
        }

        Ar >> SkinWeightProfilesData;

        // https://github.com/EpicGames/UnrealEngine/blob/380b4e3be03d6d9744891ce6f7d3798d190c0dab/Engine/Source/Runtime/Engine/Private/SkeletalMeshLODRenderData.cpp#L684
        // Not in Fortnite yet (that's a first!)
        // Ar >> RayTracingData;
    }
}