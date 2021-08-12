#include "FMovieSceneSequenceID.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FMovieSceneSequenceID& Value)
    {
        Ar >> Value.Value;

        return Ar;
    }
}