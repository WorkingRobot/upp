#include "UWorld.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/bccdec1d349b12e817b8d565884044ce6365a619/Engine/Source/Runtime/Engine/Private/World.cpp#L403
    UWorld::UWorld(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO) :
        UObject(Ar, Schema, Ctx, IsCDO)
    {
        Ar >> PersistentLevel;

        Ar >> ExtraReferencedObjects;
        Ar >> StreamingLevels;
    }
}