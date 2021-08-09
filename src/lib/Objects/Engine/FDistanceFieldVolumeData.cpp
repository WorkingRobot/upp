#include "FDistanceFieldVolumeData.h"

namespace upp::Objects {
	// https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/Engine/Private/PositionVertexBuffer.cpp#L150
    FArchive& operator>>(FArchive& Ar, FDistanceFieldVolumeData& Value)
    {
		Ar >> Value.CompressedDistanceFieldVolume;
		Ar >> Value.Size;
		Ar >> Value.LocalBoundingBox;
		Ar >> Value.DistanceMinMax;
		int bMeshWasClosed;
		Ar >> bMeshWasClosed;
		Value.MeshWasClosed = bMeshWasClosed;
		int bBuiltAsIfTwoSided;
		Ar >> bBuiltAsIfTwoSided;
		Value.BuiltAsIfTwoSided = bBuiltAsIfTwoSided;
		int bMeshWasPlane;
		Ar >> bMeshWasPlane;
		Value.MeshWasPlane = bMeshWasPlane;

		return Ar;
	}
}