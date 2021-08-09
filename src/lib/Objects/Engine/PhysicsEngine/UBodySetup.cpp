#include "UBodySetup.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/698f5318af7864d6cbbc994aec34be5b3ccb64eb/Engine/Source/Runtime/Engine/Private/PhysicsEngine/BodySetup.cpp#L1018
    UBodySetup::UBodySetup(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO) :
        UBodySetupCore(Ar, Schema, Ctx, IsCDO),
        HasCookedCollisionData(false)
    {
        Ar >> BodySetupGuid;

        int bCooked;
        Ar >> bCooked;

        if (bCooked) {
            int bHasCookedCollisionData;
            Ar >> bHasCookedCollisionData;
            HasCookedCollisionData = bHasCookedCollisionData;

            CookedFormatData.Serialize(Ar, Ctx);
        }
    }
}