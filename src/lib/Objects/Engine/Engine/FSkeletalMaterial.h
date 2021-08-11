#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "../../CoreUObject/UObject/FPackageIndex.h"
#include "../FMeshUVChannelInfo.h"

namespace upp::Objects {
    struct FSkeletalMaterial {
        FPackageIndex MaterialInterface;
        FName MaterialSlotName;
        FName ImportedMaterialSlotName;
        FMeshUVChannelInfo UVChannelData;

        friend FArchive& operator>>(FArchive& Ar, FSkeletalMaterial& Value);
    };
}