#include "FMovieSceneEvaluationKey.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FMovieSceneEvaluationKey& Value)
    {
        Ar >> Value.SequenceID;
        Ar >> Value.TrackIdentifier;
        Ar >> Value.SectionIndex;

        return Ar;
    }
}