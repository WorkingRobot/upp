#include "FMovieSceneFloatValue.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FMovieSceneFloatValue& Value)
    {
        Ar >> Value.Value;
        Ar >> Value.Tangent.ArriveTangent;
        Ar >> Value.Tangent.LeaveTangent;
        Ar >> Value.Tangent.ArriveTangentWeight;
        Ar >> Value.Tangent.LeaveTangentWeight;
        Ar >> Value.Tangent.TangentWeightMode;
        Ar >> Value.InterpMode;
        Ar >> Value.TangentMode;
        Ar >> Value.PaddingByte;

        return Ar;
    }
}