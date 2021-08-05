#pragma once

#include "../../CoreUObject/UObject/UClass.h"

namespace upp::Objects {
    struct UBlueprintGeneratedClass : public UClass {
        // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/Engine/Private/BlueprintGeneratedClass.cpp#L1715
        UBlueprintGeneratedClass(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO) : UClass(Ar, Schema, Ctx, IsCDO) { }
    };
}