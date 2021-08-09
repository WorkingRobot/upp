#pragma once

#include "../Core/Math/FBox.h"
#include "../Core/Math/FIntVector.h"
#include "../Core/Math/FVector2D.h"
#include "../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FDistanceFieldVolumeData {
        std::vector<uint8_t> CompressedDistanceFieldVolume;
        FIntVector Size;
        FBox LocalBoundingBox;
        FVector2D DistanceMinMax;
        bool MeshWasClosed;
        bool BuiltAsIfTwoSided;
        bool MeshWasPlane;

        friend FArchive& operator>>(FArchive& Ar, FDistanceFieldVolumeData& Value);
    };
}