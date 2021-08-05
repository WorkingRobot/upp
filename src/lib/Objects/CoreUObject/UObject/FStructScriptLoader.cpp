#include "FStructScriptLoader.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/CoreUObject/Private/UObject/StructScriptLoader.cpp#L157
    FStructScriptLoader::FStructScriptLoader(FArchive& Ar)
    {
        Ar >> BytecodeBufferSize;
        Ar >> SerializedScriptSize;
        ScriptSerializationOffset = Ar.Tell();
    }

    void FStructScriptLoader::LoadStructWithScript(FArchive& Ar)
    {
        constexpr bool ShouldSkipScriptSerialization = true;
        if constexpr (ShouldSkipScriptSerialization) {
            Ar.Seek(ScriptSerializationOffset + SerializedScriptSize, ESeekDir::Beg);
            return;
        }

        Ar.Seek(ScriptSerializationOffset, ESeekDir::Beg);
        // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/CoreUObject/Private/UObject/StructScriptLoader.cpp#L267
        // Locked behind upp premium on onlyfans for only $5/month
    }
}