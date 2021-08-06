#pragma once

#include "../../Core/Math/FBox.h"
#include "../../Core/Math/FColor.h"
#include "../../Core/Serialization/FArchive.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/833b26ffdf07619e3ce07d08a0820e8e18ae2f1a/Engine/Source/Runtime/Engine/Classes/Engine/Level.h#L282
    struct FPrecomputedVolumeDistanceField {
        float VolumeMaxDistance;
        FBox VolumeBox;
        int VolumeSizeX;
        int VolumeSizeY;
        int VolumeSizeZ;
        std::vector<FColor> Data;

        friend FArchive& operator>>(FArchive& Ar, FPrecomputedVolumeDistanceField& Value);
    };
}