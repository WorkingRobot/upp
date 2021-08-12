#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "../FMovieSceneSequenceID.h"
#include "FMovieSceneTrackIdentifier.h"

namespace upp::Objects {
    struct FMovieSceneEvaluationKey {
        FMovieSceneSequenceID SequenceID;
        FMovieSceneTrackIdentifier TrackIdentifier;
        uint32_t SectionIndex;

        friend FArchive& operator>>(FArchive& Ar, FMovieSceneEvaluationKey& Value);
    };
}