#include "FWeightedRandomSampler.h"

namespace upp::Objects {
	// https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/Engine/Private/WeightedRandomSampler.cpp#L78
    FArchive& operator>>(FArchive& Ar, FWeightedRandomSampler& Value)
    {
		Ar >> Value.Prob;
		Ar >> Value.Alias;
		Ar >> Value.TotalWeight;

		return Ar;
	}
}