#pragma once

#include "EClassFlags.h"
#include "FImplementedInterface.h"
#include "UStruct.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/CoreUObject/Public/UObject/Class.h#L1720
    struct UClass : public UStruct {
        std::vector<std::pair<FName, FPackageIndex>> FuncMap;
        EClassFlags ClassFlags;
        FPackageIndex ClassWithin;
        FName ClassConfigName;
        FPackageIndex ClassGeneratedBy;
        std::vector<FImplementedInterface> Interfaces;
        bool IsCooked;

        FPackageIndex ClassDefaultObject;

        UClass(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO);
    };
}