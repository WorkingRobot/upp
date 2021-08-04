#pragma once

#include "../../CoreUObject/UObject/UObject.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/65cbeac6d1bdefdf560f3f879db3f599cf166a3c/Engine/Source/Runtime/Engine/Private/SoundBase.cpp#L223
    struct USoundBase : public UObject {
        USoundBase(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO) : UObject(Ar, Schema, Ctx, IsCDO) { }
    };
}