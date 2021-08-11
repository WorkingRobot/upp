#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "../../CoreUObject/UObject/FSerializeCtx.h"
#include "../Animation/FSkinWeightProfilesData.h"
#include "../FStaticMeshVertexBuffers.h"
#include "FMultiSizeIndexContainer.h"
#include "FSkeletalMeshVertexClothBuffer.h"
#include "FSkelMeshRenderSection.h"
#include "FSkinWeightVertexBuffer.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/AnimationCore/Public/BoneIndices.h#L7
    using FBoneIndexType = uint16_t;

    struct FSkeletalMeshLODRenderData {
        std::vector<FBoneIndexType> RequiredBones;
        std::vector<FSkelMeshRenderSection> RenderSections;
        std::vector<FBoneIndexType> ActiveBoneIndices;
        uint32_t BuffersSize;
        FMultiSizeIndexContainer MultiSizeIndexContainer;
        FStaticMeshVertexBuffers StaticVertexBuffers;
        FSkinWeightVertexBuffer SkinWeightVertexBuffer;
        FMultiSizeIndexContainer AdjacencyMultiSizeIndexContainer;
        FSkeletalMeshVertexClothBuffer ClothVertexBuffer;
        FSkinWeightProfilesData SkinWeightProfilesData;
        std::vector<uint8_t> RayTracingData;

        void Serialize(FArchive& Ar, FSerializeCtx& Ctx, bool HasVertexColors);

        bool HasClothData() const;

    private:
        void SerializeStreamedData(FArchive& Ar, bool HasVertexColors);
    };
}