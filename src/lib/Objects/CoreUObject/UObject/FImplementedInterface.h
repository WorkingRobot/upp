#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "FPackageIndex.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/CoreUObject/Public/UObject/Class.h#L2500
    struct FImplementedInterface {
        FPackageIndex Class;
        int PointerOffset;
        bool IsImplementedByK2;

        friend FArchive& operator>>(FArchive& Ar, FImplementedInterface& Value);
    };
}