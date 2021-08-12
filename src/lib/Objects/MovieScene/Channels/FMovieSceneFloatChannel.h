#pragma once

#include "../../Core/Misc/FFrameNumber.h"
#include "../../Core/Misc/FFrameRate.h"
#include "../../Core/Serialization/FArchive.h"
#include "../../Engine/Curves/ERichCurveExtrapolation.h"
#include "FMovieSceneFloatValue.h"

namespace upp::Objects {
    struct FMovieSceneFloatChannel {
        ERichCurveExtrapolation PreInfinityExtrap;
        ERichCurveExtrapolation PostInfinityExtrap;
        std::vector<FFrameNumber> Times;
        std::vector<FMovieSceneFloatValue> Values;
        float DefaultValue;
        bool HasDefaultValue;
        FFrameRate TickResolution;

        friend FArchive& operator>>(FArchive& Ar, FMovieSceneFloatChannel& Value);
    };
}