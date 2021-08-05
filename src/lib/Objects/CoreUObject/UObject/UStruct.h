#pragma once

#include "FProperty.h"
#include "UField.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/CoreUObject/Public/UObject/Class.h#L296
    struct UStruct : public UField {
        FPackageIndex SuperStruct;
        std::vector<FPackageIndex> Children;
        std::vector<FProperty> ChildProperties;
        
        UStruct(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO);
    };
}