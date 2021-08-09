#include "FStaticMeshVertexBuffer.h"

#include "FStripDataFlags.h"

namespace upp::Objects {
	// https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/Engine/Private/Rendering/StaticMeshVertexBuffer.cpp#L202
    FArchive& operator>>(FArchive& Ar, FStaticMeshVertexBuffer& Value)
    {
		FStripDataFlags StripFlags;
		Ar >> StripFlags;

		Ar >> Value.NumTexCoords;
		Ar >> Value.NumVertices;
		int bUseFullPrecisionUVs;
		Ar >> bUseFullPrecisionUVs;
		int bUseHighPrecisionTangentBasis;
		Ar >> bUseHighPrecisionTangentBasis;

		if (!StripFlags.IsDataStrippedForServer()) {
			if (bUseHighPrecisionTangentBasis) {
				Ar.BulkSerialize(Value.TangentsData.emplace<std::vector<std::pair<FPackedRGBA16N, FPackedRGBA16N>>>());
			}
			else {
				Ar.BulkSerialize(Value.TangentsData.emplace<std::vector<std::pair<FPackedNormal, FPackedNormal>>>());
			}
			if (bUseFullPrecisionUVs) {
				Ar.BulkSerialize(Value.TexcoordData.emplace<std::vector<FVector2D>>());
			}
			else {
				Ar.BulkSerialize(Value.TexcoordData.emplace<std::vector<FVector2DHalf>>());
			}
		}

		return Ar;
	}
}