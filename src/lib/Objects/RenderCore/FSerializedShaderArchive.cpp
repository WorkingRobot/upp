#include "FSerializedShaderArchive.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/RenderCore/Private/ShaderCodeArchive.cpp#L195
    FArchive& operator>>(FArchive& Ar, FSerializedShaderArchive& Value)
    {
        Ar >> Value.ShaderMapHashes;
        Ar >> Value.ShaderHashes;
        Ar >> Value.ShaderMapEntries;
        Ar >> Value.ShaderEntries;
        Ar >> Value.PreloadEntries;
        Ar >> Value.ShaderIndices;

        return Ar;
    }
}