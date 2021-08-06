#pragma once

#include "../../Core/Math/FVector2D.h"
#include "../../Core/Serialization/FArchive.h"
#include "FPrecomputedVisibilityBucket.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/833b26ffdf07619e3ce07d08a0820e8e18ae2f1a/Engine/Source/Runtime/Engine/Classes/Engine/Level.h#L220
    struct FPrecomputedVisibilityHandler {
        FVector2D PrecomputedVisibilityCellBucketOriginXY;
        float PrecomputedVisibilityCellSizeXY;
        float PrecomputedVisibilityCellSizeZ;
        int PrecomputedVisibilityCellBucketSizeXY;
        int PrecomputedVisibilityNumCellBuckets;
        std::vector<FPrecomputedVisibilityBucket> PrecomputedVisibilityCellBuckets;

        friend FArchive& operator>>(FArchive& Ar, FPrecomputedVisibilityHandler& Value);
    };
}