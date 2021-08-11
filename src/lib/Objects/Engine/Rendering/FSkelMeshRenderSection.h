#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "../ESkinVertexColorChannel.h"
#include "../FClothingSectionData.h"
#include "../FMeshToMeshVertData.h"
#include "FDuplicatedVerticesBuffer.h"

namespace upp::Objects {
	// https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/AnimationCore/Public/BoneIndices.h#L7
	using FBoneIndexType = uint16_t;

    struct FSkelMeshRenderSection {
        uint16_t MaterialIndex;
		uint32_t BaseIndex;
		uint32_t NumTriangles;
		bool RecomputeTangent;
		ESkinVertexColorChannel RecomputeTangentsVertexMaskChannel;
		bool CastShadow;
		uint32_t BaseVertexIndex;
		std::vector<FMeshToMeshVertData> ClothMappingData;
		std::vector<FBoneIndexType> BoneMap;
		uint32_t NumVertices;
		int32_t MaxBoneInfluences;
		int16_t CorrespondClothAssetIndex;
		FClothingSectionData ClothingData;
		FDuplicatedVerticesBuffer DuplicatedVerticesBuffer;
		bool Disabled;

        friend FArchive& operator>>(FArchive& Ar, FSkelMeshRenderSection& Value);
    };
}