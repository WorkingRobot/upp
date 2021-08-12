#pragma once

#include "../Serialization/FArchive.h"
#include "TRangeBound.h"

namespace upp::Objects {
    template<class T>
	struct TRange {
        TRangeBound<T> LowerBound;
        TRangeBound<T> UpperBound;

        friend FArchive& operator>>(FArchive& Ar, TRange& Value)
        {
            Ar >> Value.LowerBound;
            Ar >> Value.UpperBound;

            return Ar;
        }
	};
}