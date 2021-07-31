#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "../../Core/UObject/FName.h"

namespace upp::Objects {
    // UE marks this as a typedef for TScriptDelegate<>,
    // but it's not allowed to be templated outside of just <>
    // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/Core/Public/UObject/ScriptDelegates.h#L25
    struct FScriptDelegate {
        int Object; // FWeakObjectPtr
        FName FunctionName;

        friend FArchive& operator>>(FArchive& Ar, FScriptDelegate& Value);
    };
}