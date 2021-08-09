#include "FColorVertexBuffer.h"

#include "FStripDataFlags.h"

namespace upp::Objects {
	// https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/Engine/Private/Rendering/ColorVertexBuffer.cpp#L195
    FArchive& operator>>(FArchive& Ar, FColorVertexBuffer& Value)
    {
		FStripDataFlags StripFlags;
		Ar >> StripFlags;

		Ar >> Value.Stride;
		Ar >> Value.NumVertices;

		if (!StripFlags.IsDataStrippedForServer() && Value.NumVertices > 0) {
			Ar.BulkSerialize(Value.VertexData);
		}

		return Ar;
	}
}