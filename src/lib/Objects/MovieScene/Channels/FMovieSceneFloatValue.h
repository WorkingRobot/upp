#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "../../Engine/Curves/ERichCurveInterpMode.h"
#include "../../Engine/Curves/ERichCurveTangentMode.h"
#include "FMovieSceneTangentData.h"

namespace upp::Objects {
    struct FMovieSceneFloatValue {
        float Value;
        FMovieSceneTangentData Tangent;
        ERichCurveInterpMode InterpMode;
        ERichCurveTangentMode TangentMode;
        uint8_t PaddingByte;

        friend FArchive& operator>>(FArchive& Ar, FMovieSceneFloatValue& Value);
    };
}