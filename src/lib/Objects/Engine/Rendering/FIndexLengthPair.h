#pragma once

#include <utility>

namespace upp::Objects {
    // (Length, Index)
    // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/Engine/Public/Rendering/SkeletalMeshDuplicatedVerticesBuffer.h#L9
    using FIndexLengthPair = std::pair<uint32_t, uint32_t>;
}