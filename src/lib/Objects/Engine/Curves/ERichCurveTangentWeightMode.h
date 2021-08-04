#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class ERichCurveTangentWeightMode : uint8_t {
		/** Don't take tangent weights into account. */
		RCTWM_WeightedNone,
		/** Only take the arrival tangent weight into account for evaluation. */
		RCTWM_WeightedArrive,
		/** Only take the leaving tangent weight into account for evaluation. */
		RCTWM_WeightedLeave,
		/** Take both the arrival and leaving tangent weights into account for evaluation. */
		RCTWM_WeightedBoth
    };
}