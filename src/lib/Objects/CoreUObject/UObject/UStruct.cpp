#include "UStruct.h"

#include "FStructScriptLoader.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/CoreUObject/Private/UObject/Class.cpp#L1795
    UStruct::UStruct(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO) :
        UField(Ar, Schema, Ctx, IsCDO)
    {
        Ar >> SuperStruct;
        Ar >> Children;

        // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/CoreUObject/Private/UObject/Class.cpp#L1723
        int PropertyCount;
        Ar >> PropertyCount;
        ChildProperties.reserve(PropertyCount);
        for (int Idx = 0; Idx < PropertyCount; ++Idx) {
            FName PropertyTypeName;
            Ar >> PropertyTypeName;
            ChildProperties.emplace_back(Ar, PropertyTypeName);
        }

        FStructScriptLoader ScriptLoadHelper(Ar);
        ScriptLoadHelper.LoadStructWithScript(Ar);
    }
}