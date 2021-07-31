#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "FScriptDelegate.h"

namespace upp::Objects {
    // UE marks this as a typedef for TMulticastScriptDelegate<>,
    // but it's not allowed to be templated outside of just <>
    struct FMulticastScriptDelegate {
        // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/Core/Public/UObject/ScriptDelegates.h#L613
        std::vector<FScriptDelegate> InvocationList;

        friend FArchive& operator>>(FArchive& Ar, FMulticastScriptDelegate& Value);
    };
}