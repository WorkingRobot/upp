#pragma once

#include "FFormatArgumentValue.h"

#include <string>
#include <vector>

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/Core/Public/Internationalization/Text.h#L148
    using FFormatNamedArguments = std::vector<std::pair<std::string, FFormatArgumentValue>>;
}