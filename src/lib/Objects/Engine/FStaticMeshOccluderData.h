#pragma once

#include "../Core/Math/FVector.h"
#include "../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FStaticMeshOccluderData {
        // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/Engine/Public/SceneManagement.h#L2045
        // No "SP" suffix because it's not shared anymore
        std::vector<FVector> Vertices;
        std::vector<uint16_t> Indices;

        friend FArchive& operator>>(FArchive& Ar, FStaticMeshOccluderData& Value);
    };
}