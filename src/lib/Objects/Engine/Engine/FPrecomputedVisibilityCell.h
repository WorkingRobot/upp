#pragma once

#include "../../Core/Math/FVector.h"
#include "../../Core/Serialization/FArchive.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/833b26ffdf07619e3ce07d08a0820e8e18ae2f1a/Engine/Source/Runtime/Engine/Classes/Engine/Level.h#L200
    struct FPrecomputedVisibilityCell {
        FVector Min;
        uint16_t ChunkIndex;
        uint16_t DataOffset;

        friend FArchive& operator>>(FArchive& Ar, FPrecomputedVisibilityCell& Value);
    };
}