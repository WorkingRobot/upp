#include "FMulticastScriptDelegate.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FMulticastScriptDelegate& Value)
    {
        // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/Core/Public/UObject/ScriptDelegates.h#L441
        Ar >> Value.InvocationList;

        return Ar;
    }
}