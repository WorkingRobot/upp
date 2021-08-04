#include "FRichCurveKey.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FRichCurveKey& Value)
    {
		Ar >> Value.InterpMode;
		Ar >> Value.TangentMode;
		Ar >> Value.TangentWeightMode;
		Ar >> Value.Time;
		Ar >> Value.Value;
		Ar >> Value.ArriveTangent;
		Ar >> Value.ArriveTangentWeight;
		Ar >> Value.LeaveTangent;
		Ar >> Value.LeaveTangentWeight;

        return Ar;
    }
}