#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "../../Engine/Curves/ERichCurveTangentWeightMode.h"

namespace upp::Objects {
    struct FMovieSceneTangentData {
        float ArriveTangent;
        float LeaveTangent;
        float ArriveTangentWeight;
        float LeaveTangentWeight;
        ERichCurveTangentWeightMode TangentWeightMode;

        friend FArchive& operator>>(FArchive& Ar, FMovieSceneTangentData& Value);
    };
}