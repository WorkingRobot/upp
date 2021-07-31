#pragma once

#include "../../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FScriptInterface {
        uint32_t ObjectRef;

        // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/CoreUObject/Private/UObject/PropertyInterface.cpp#L139
        friend FArchive& operator>>(FArchive& Ar, FScriptInterface& Value);
    };
}