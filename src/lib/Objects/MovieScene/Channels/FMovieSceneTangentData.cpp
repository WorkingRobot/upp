#include "FMovieSceneTangentData.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FMovieSceneTangentData& Value)
    {
        Ar >> Value.ArriveTangent;
        Ar >> Value.LeaveTangent;
        Ar >> Value.ArriveTangentWeight;
        Ar >> Value.LeaveTangentWeight;
        Ar >> Value.TangentWeightMode;

        return Ar;
    }
}