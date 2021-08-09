#pragma once

#include "../../CoreUObject/UObject/UObject.h"

namespace upp::Objects {
    struct UBodySetupCore : public UObject {
        // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/PhysicsCore/Public/BodySetupCore.h#L18
        UBodySetupCore(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO) : UObject(Ar, Schema, Ctx, IsCDO) { }
    };
}