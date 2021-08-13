#include "FShaderCodeArchive.h"

namespace upp::Objects {
    FShaderCodeArchive::FShaderCodeArchive(FArchive& Ar)
    {
        Ar >> *this;
    }

    // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/RenderCore/Private/ShaderCodeLibrary.cpp#L984
    FArchive& operator>>(FArchive& Ar, FShaderCodeArchive& Value)
    {
        Ar >> Value.ArchiveVersion;

        if (Value.ArchiveVersion == 2) {
            Ar >> Value.SerializedShaders;
            auto& Entries = Value.SerializedShaders.ShaderEntries;
            Value.ShaderCode.resize(Entries.size());
            for (int Idx = 0; Idx < Entries.size(); ++Idx) {
                Value.ShaderCode[Idx].resize(Entries[Idx].Size);
            }
            for (int Idx = 0; Idx < Entries.size(); ++Idx) {
                Ar.ReadBuffer(Value.ShaderCode[Idx], Entries[Idx].Size);
            }
        }
#ifdef _DEBUG
        else {
            _CrtDbgBreak();
        }
#endif

        return Ar;
    }
}