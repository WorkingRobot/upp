#include "FMovieSceneFrameRange.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FMovieSceneFrameRange& Value)
    {
        Ar >> Value.Value;

        return Ar;
    }
}