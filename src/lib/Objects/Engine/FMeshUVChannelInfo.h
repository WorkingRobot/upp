#pragma once

#include "../Core/Math/FVector.h"
#include "../Core/Math/FVector2D.h"
#include "../Core/Math/FVector4.h"
#include "../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FMeshUVChannelInfo {
        static constexpr int MAX_TEXCOORDS = 4;

        bool Initialized;
        bool OverrideDensities;
        float LocalUVDensities[MAX_TEXCOORDS];

        friend FArchive& operator>>(FArchive& Ar, FMeshUVChannelInfo& Value);
    };
}