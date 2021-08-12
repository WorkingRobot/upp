#include "FMovieSceneEvaluationTreeNode.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FMovieSceneEvaluationTreeNode& Value)
    {
        Ar >> Value.Range;
        Ar >> Value.Parent;
        Ar >> Value.ChildrenID;
        Ar >> Value.DataID;

        return Ar;
    }
}