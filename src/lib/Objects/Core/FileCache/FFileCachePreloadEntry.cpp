#include "FFileCachePreloadEntry.h"

namespace upp::Objects {
    // The fact that this code is no where near the struct's declaration is a testament to the jankiness of UE
    // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/RenderCore/Public/ShaderCodeArchive.h#L24
    FArchive& operator>>(FArchive& Ar, FFileCachePreloadEntry& Value)
    {
        Ar >> Value.Offset;
        Ar >> Value.Size;

        return Ar;
    }
}