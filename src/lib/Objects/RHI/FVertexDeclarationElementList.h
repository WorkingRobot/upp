#pragma once

#include "FVertexElement.h"

#include <vector>

namespace upp::Objects {
    // UE4 can't allocate more than 16 elements
    // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/RHI/Public/RHIDefinitions.h#L593
    using FVertexDeclarationElementList = std::vector<FVertexElement>;
}