#include "FModelVertexBuffer.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/Engine/Private/ModelRender.cpp#L66
    FArchive& operator>>(FArchive& Ar, FModelVertexBuffer& Value)
    {
        Ar >> Value.Vertices;

        return Ar;
    }
}