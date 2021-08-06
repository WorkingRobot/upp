#include "FLightmassPrimitiveSettings.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/Engine/Private/Polygon.cpp#L26
    FArchive& operator>>(FArchive& Ar, FLightmassPrimitiveSettings& Value)
    {
        int Bool;

        Ar >> Bool;
        Value.UseTwoSidedLighting = Bool;

        Ar >> Bool;
        Value.ShadowIndirectOnly = Bool;

        Ar >> Value.FullyOccludedSamplesFraction;

        Ar >> Bool;
        Value.UseEmissiveForStaticLighting = Bool;

        Ar >> Bool;
        Value.UseVertexNormalForHemisphereGather = Bool;

        Ar >> Value.EmissiveLightFalloffExponent;
        Ar >> Value.EmissiveLightExplicitInfluenceRadius;
        Ar >> Value.EmissiveBoost;
        Ar >> Value.DiffuseBoost;

        return Ar;
    }
}