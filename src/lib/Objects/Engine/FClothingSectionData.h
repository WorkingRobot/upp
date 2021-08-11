#pragma once

#include "../Core/Misc/FGuid.h"
#include "../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FClothingSectionData {
        FGuid AssetGuid;
        int AssetLodIndex;

        friend FArchive& operator>>(FArchive& Ar, FClothingSectionData& Value);
    };
}