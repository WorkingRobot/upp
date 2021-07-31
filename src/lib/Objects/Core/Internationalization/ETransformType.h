#pragma once

#include <stdint.h>

namespace upp::Objects {
	// https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/Core/Private/Internationalization/TextHistory.h#L584
	enum class ETransformType : uint8_t
	{
		ToLower = 0,
		ToUpper,

		// Add new enum types at the end only! They are serialized by index.
	};
}