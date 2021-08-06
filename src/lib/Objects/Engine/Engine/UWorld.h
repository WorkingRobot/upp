#pragma once

#include "../../CoreUObject/UObject/UObject.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/bccdec1d349b12e817b8d565884044ce6365a619/Engine/Source/Runtime/Engine/Classes/Engine/World.h#L894
    struct UWorld : public UObject {
        FPackageIndex PersistentLevel;
        std::vector<FPackageIndex> ExtraReferencedObjects;
        std::vector<FPackageIndex> StreamingLevels;

        UWorld(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO);
    };
}