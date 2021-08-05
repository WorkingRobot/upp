#pragma once

#include "UObject.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/CoreUObject/Public/UObject/Class.h#L65
    struct UField : public UObject {
        UField(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO) : UObject(Ar, Schema, Ctx, IsCDO) { }
    };
}