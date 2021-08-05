#pragma once

#include "EFunctionFlags.h"
#include "UStruct.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/CoreUObject/Public/UObject/Class.h#L1720
    struct UFunction : public UStruct {
        EFunctionFlags FunctionFlags;
        FPackageIndex EventGraphFunction;
        int32_t EventGraphCallOffset;

        UFunction(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO);
    };
}