#pragma once

#include "../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FMovieSceneSequenceID {
        uint32_t Value;

        friend FArchive& operator>>(FArchive& Ar, FMovieSceneSequenceID& Value);
    };
}