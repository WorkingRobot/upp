#include "FStaticMeshOccluderData.h"

namespace upp::Objects {
	// https://github.com/EpicGames/UnrealEngine/blob/d2acf8eff721d88a654648c6ac1c43137ae4dc23/Engine/Source/Runtime/Engine/Private/StaticMesh.cpp#L1814
    FArchive& operator>>(FArchive& Ar, FStaticMeshOccluderData& Value)
    {
		int bHasOccluderData;
		Ar >> bHasOccluderData;
		if (bHasOccluderData) {
			Ar.BulkSerialize(Value.Vertices);
			Ar.BulkSerialize(Value.Indices);
		}

		return Ar;
	}
}