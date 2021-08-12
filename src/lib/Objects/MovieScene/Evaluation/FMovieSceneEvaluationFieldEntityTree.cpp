#include "FMovieSceneEvaluationFieldEntityTree.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FMovieSceneEvaluationFieldEntityTree& Value)
    {
        Ar >> Value.SerializedData;

        return Ar;
    }
}