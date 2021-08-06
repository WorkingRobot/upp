#include "ULevel.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/833b26ffdf07619e3ce07d08a0820e8e18ae2f1a/Engine/Source/Runtime/Engine/Private/Level.cpp#L385
    ULevel::ULevel(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO) :
        UObject(Ar, Schema, Ctx, IsCDO)
    {
        Ar >> Actors;

        Ar >> Url;
        Ar >> Model;
        Ar >> ModelComponents;

        Ar >> LevelScriptActor;

        Ar >> NavListStart;
        Ar >> NavListEnd;

        Ar >> PrecomputedVisibilityHandler;
        Ar >> PrecomputedVolumeDistanceField;
    }
}