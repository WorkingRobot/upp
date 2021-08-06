#pragma once

#include "../../CoreUObject/UObject/UObject.h"
#include "FPrecomputedVisibilityHandler.h"
#include "FPrecomputedVolumeDistanceField.h"
#include "FURL.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/833b26ffdf07619e3ce07d08a0820e8e18ae2f1a/Engine/Source/Runtime/Engine/Classes/Engine/Level.h#L412
    struct ULevel : public UObject {
        std::vector<FPackageIndex> Actors;
        FURL Url;
        FPackageIndex Model;
        std::vector<FPackageIndex> ModelComponents;
        FPackageIndex LevelScriptActor;
        FPackageIndex NavListStart;
        FPackageIndex NavListEnd;
        FPrecomputedVisibilityHandler PrecomputedVisibilityHandler;
        FPrecomputedVolumeDistanceField PrecomputedVolumeDistanceField;

        ULevel(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO);
    };
}