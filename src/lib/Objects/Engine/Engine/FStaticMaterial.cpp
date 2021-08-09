#include "FStaticMaterial.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/d2acf8eff721d88a654648c6ac1c43137ae4dc23/Engine/Source/Runtime/Engine/Private/StaticMesh.cpp#L2723
    FArchive& operator>>(FArchive& Ar, FStaticMaterial& Value)
    {
        Ar >> Value.MaterialInterface;
        Ar >> Value.MaterialSlotName;
        Ar >> Value.UVChannelData;

        return Ar;
    }
}