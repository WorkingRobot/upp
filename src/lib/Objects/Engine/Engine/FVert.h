#pragma once

#include "../../Core/Math/FVector2D.h"
#include "../../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FVert {
        int pVertex;
        int iSide;
        FVector2D ShadowTexCoord;
        FVector2D BackfaceShadowTexCoord;

        friend FArchive& operator>>(FArchive& Ar, FVert& Value);
    };
}