#pragma once

#include "../../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FLightmassPrimitiveSettings {
        bool UseTwoSidedLighting;
        bool ShadowIndirectOnly;
        float FullyOccludedSamplesFraction;
        bool UseEmissiveForStaticLighting;
        bool UseVertexNormalForHemisphereGather;
        float EmissiveLightFalloffExponent;
        float EmissiveLightExplicitInfluenceRadius;
        float EmissiveBoost;
        float DiffuseBoost;

        friend FArchive& operator>>(FArchive& Ar, FLightmassPrimitiveSettings& Value);
    };
}