#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class ERichCurveTangentMode : uint8_t {
		/** Automatically calculates tangents to create smooth curves between values. */
		RCTM_Auto,
		/** User specifies the tangent as a unified tangent where the two tangents are locked to each other, presenting a consistent curve before and after. */
		RCTM_User,
		/** User specifies the tangent as two separate broken tangents on each side of the key which can allow a sharp change in evaluation before or after. */
		RCTM_Break,
		/** No tangents. */
		RCTM_None
    };
}