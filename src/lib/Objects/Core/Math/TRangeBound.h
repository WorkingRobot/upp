#pragma once

#include "../Serialization/FArchive.h"
#include "ERangeBoundTypes.h"

namespace upp::Objects {
    template<class T>
	struct TRangeBound {
        ERangeBoundTypes Type;
        T Value;

        friend FArchive& operator>>(FArchive& Ar, TRangeBound& Value)
        {
            Ar >> Value.Type;
            Ar >> Value.Value;

            return Ar;
        }
	};
}