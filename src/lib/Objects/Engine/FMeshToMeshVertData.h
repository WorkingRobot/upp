#pragma once

#include "../Core/Math/FVector4.h"
#include "../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FMeshToMeshVertData {
        FVector4 PositionBaryCoordsAndDist;
        FVector4 NormalBaryCoordsAndDist;
        FVector4 TangentBaryCoordsAndDist;
        uint16_t SourceMeshVertIndices[4];
        float Weight;
        uint32_t Padding;

        friend FArchive& operator>>(FArchive& Ar, FMeshToMeshVertData& Value);
    };
}