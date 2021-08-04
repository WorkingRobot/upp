#include "FSimpleCurveKey.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FSimpleCurveKey& Value)
    {
		Ar >> Value.Time;
		Ar >> Value.Value;

        return Ar;
    }
}