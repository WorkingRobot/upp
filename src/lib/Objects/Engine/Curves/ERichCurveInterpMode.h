#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class ERichCurveInterpMode : uint8_t {
		/** Use linear interpolation between values. */
		RCIM_Linear,
		/** Use a constant value. Represents stepped values. */
		RCIM_Constant,
		/** Cubic interpolation. See TangentMode for different cubic interpolation options. */
		RCIM_Cubic,
		/** No interpolation. */
		RCIM_None
    };
}