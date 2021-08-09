#pragma once

#include "../Core/Math/FVector.h"
#include "../Core/Math/FVector2D.h"
#include "../Core/Math/FVector4.h"
#include "../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FModelVertex {
        FVector Position;
        FVector TangentX;
        FVector4 TangentZ;
        FVector2D TexCoord;
        FVector2D ShadowTexCoord;

        friend FArchive& operator>>(FArchive& Ar, FModelVertex& Value);
    };
}