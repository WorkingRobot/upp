#pragma once

#include "../Core/Math/TRange.h"
#include "../Core/Misc/FFrameNumber.h"
#include "../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FMovieSceneFrameRange {
        TRange<FFrameNumber> Value;

        friend FArchive& operator>>(FArchive& Ar, FMovieSceneFrameRange& Value);
    };
}