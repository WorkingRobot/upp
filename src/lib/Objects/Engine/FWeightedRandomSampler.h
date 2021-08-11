#pragma once

#include "../Core/Math/FVector.h"
#include "../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FWeightedRandomSampler {
        std::vector<float> Prob;
        std::vector<int> Alias;
        float TotalWeight;

        friend FArchive& operator>>(FArchive& Ar, FWeightedRandomSampler& Value);
    };

    // https://github.com/EpicGames/UnrealEngine/blob/d2acf8eff721d88a654648c6ac1c43137ae4dc23/Engine/Source/Runtime/Engine/Public/StaticMeshResources.h#L246
    using FStaticMeshAreaWeightedSectionSampler = FWeightedRandomSampler;

    // https://github.com/EpicGames/UnrealEngine/blob/d2acf8eff721d88a654648c6ac1c43137ae4dc23/Engine/Source/Runtime/Engine/Public/StaticMeshResources.h#L234
    using FStaticMeshSectionAreaWeightedTriangleSampler = FWeightedRandomSampler;

    // https://github.com/EpicGames/UnrealEngine/blob/adb0f8832c780488c0e4298a6af161881f95e33d/Engine/Source/Runtime/Engine/Classes/Engine/SkeletalMeshSampling.h#L12
    using FSkeletalMeshAreaWeightedTriangleSampler = FWeightedRandomSampler;
}