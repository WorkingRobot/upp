#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "../FWeightedRandomSampler.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/adb0f8832c780488c0e4298a6af161881f95e33d/Engine/Source/Runtime/Engine/Classes/Engine/SkeletalMeshSampling.h#L59
    struct FSkeletalMeshSamplingLODBuiltData {
        FSkeletalMeshAreaWeightedTriangleSampler AreaWeightedTriangleSampler;

        friend FArchive& operator>>(FArchive& Ar, FSkeletalMeshSamplingLODBuiltData& Value);
    };
}