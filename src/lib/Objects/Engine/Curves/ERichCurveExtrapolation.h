#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class ERichCurveExtrapolation : uint8_t {
		/** Repeat the curve without an offset. */
		RCCE_Cycle,
		/** Repeat the curve with an offset relative to the first or last key's value. */
		RCCE_CycleWithOffset,
		/** Sinusoidally extrapolate. */
		RCCE_Oscillate,
		/** Use a linearly increasing value for extrapolation.*/
		RCCE_Linear,
		/** Use a constant value for extrapolation */
		RCCE_Constant,
		/** No Extrapolation */
		RCCE_None
    };
}