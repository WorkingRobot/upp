#include "FMovieSceneTrackIdentifier.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FMovieSceneTrackIdentifier& Value)
    {
        Ar >> Value.Value;

        return Ar;
    }
}