#pragma once

#include "../../CoreUObject/Serialization/FFormatContainer.h"
#include "UBodySetupCore.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/698f5318af7864d6cbbc994aec34be5b3ccb64eb/Engine/Source/Runtime/Engine/Classes/PhysicsEngine/BodySetup.h#L145
    struct UBodySetup : public UBodySetupCore {
        FGuid BodySetupGuid;
        bool HasCookedCollisionData;
        FFormatContainer CookedFormatData;

        UBodySetup(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO);
    };
}