#include "FMovieSceneEvaluationTree.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FMovieSceneEvaluationTree& Value)
    {
        Ar >> Value.RootNode;
        Ar >> Value.ChildNodes;

        return Ar;
    }
}