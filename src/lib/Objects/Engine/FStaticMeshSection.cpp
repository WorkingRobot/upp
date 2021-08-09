#include "FStaticMeshSection.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/048ce1606af8daff143a1e99255aca9c6f04d46c/Engine/Source/Runtime/Engine/Private/StaticMesh.cpp#L239
    FArchive& operator>>(FArchive& Ar, FStaticMeshSection& Value)
    {
		Ar >> Value.MaterialIndex;
		Ar >> Value.FirstIndex;
		Ar >> Value.NumTriangles;
		Ar >> Value.MinVertexIndex;
		Ar >> Value.MaxVertexIndex;
		int bEnableCollision;
		Ar >> bEnableCollision;
		Value.EnableCollision = bEnableCollision;
		int bCastShadow;
		Ar >> bCastShadow;
		Value.CastShadow = bCastShadow;

		int bForceOpaque;
		Ar >> bForceOpaque;
		Value.ForceOpaque = bForceOpaque;

		int bVisibleInRayTracing;
		Ar >> bVisibleInRayTracing;
		Value.VisibleInRayTracing = bVisibleInRayTracing;

		return Ar;
	}
}