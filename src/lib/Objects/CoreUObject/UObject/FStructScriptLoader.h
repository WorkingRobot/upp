#pragma once

#include "../../Core/Serialization/FArchive.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/CoreUObject/Private/UObject/StructScriptLoader.h#L15
    struct FStructScriptLoader {
        int BytecodeBufferSize;
        int SerializedScriptSize;
        int64_t ScriptSerializationOffset;

        FStructScriptLoader(FArchive& Ar);

        void LoadStructWithScript(FArchive& Ar);
    };
}