#include "FPositionVertexBuffer.h"

namespace upp::Objects {
	// https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/Engine/Private/PositionVertexBuffer.cpp#L150
    FArchive& operator>>(FArchive& Ar, FPositionVertexBuffer& Value)
    {
		Ar >> Value.Stride;
		Ar >> Value.NumVertices;
		Ar.BulkSerialize(Value.VertexData);

		return Ar;
	}
}