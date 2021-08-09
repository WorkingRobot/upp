#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "../../CoreUObject/UObject/FPackageIndex.h"
#include "../FMeshUVChannelInfo.h"

namespace upp::Objects {
    struct FStaticMaterial {
        FPackageIndex MaterialInterface;
        FName MaterialSlotName;
        FMeshUVChannelInfo UVChannelData;

        friend FArchive& operator>>(FArchive& Ar, FStaticMaterial& Value);
    };
}