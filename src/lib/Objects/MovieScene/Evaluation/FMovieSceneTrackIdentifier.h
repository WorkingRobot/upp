#pragma once

#include "../../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FMovieSceneTrackIdentifier {
        uint32_t Value;

        friend FArchive& operator>>(FArchive& Ar, FMovieSceneTrackIdentifier& Value);
    };
}