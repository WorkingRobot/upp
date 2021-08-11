#include "FSkelMeshRenderSection.h"

#include "../FStripDataFlags.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FSkelMeshRenderSection& Value)
    {
		constexpr uint8_t DuplicatedVertices = 1;

		FStripDataFlags StripFlags;
		Ar >> StripFlags;

        Ar >> Value.MaterialIndex;
		Ar >> Value.BaseIndex;
		Ar >> Value.NumTriangles;

		int bRecomputeTangent;
		Ar >> bRecomputeTangent;
		Value.RecomputeTangent = bRecomputeTangent;

		Ar >> Value.RecomputeTangentsVertexMaskChannel;

		int bCastShadow;
		Ar >> bCastShadow;
		Value.CastShadow = bCastShadow;

		Ar >> Value.BaseVertexIndex;
		Ar >> Value.ClothMappingData;
		Ar >> Value.BoneMap;
		Ar >> Value.NumVertices;
		Ar >> Value.MaxBoneInfluences;
		Ar >> Value.CorrespondClothAssetIndex;
		Ar >> Value.ClothingData;
		if (!StripFlags.IsClassDataStripped(DuplicatedVertices)) {
			Ar >> Value.DuplicatedVerticesBuffer;
		}

		int bDisabled;
		Ar >> bDisabled;
		Value.Disabled = bDisabled;

        return Ar;
    }
}