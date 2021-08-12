#include "FMovieSceneEvaluationTreeNodeHandle.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FMovieSceneEvaluationTreeNodeHandle& Value)
    {
        Ar >> Value.ChildrenHandle;
        Ar >> Value.Index;

        return Ar;
    }
}