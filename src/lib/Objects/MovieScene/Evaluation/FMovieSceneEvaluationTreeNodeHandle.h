#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "FEvaluationTreeEntryHandle.h"

namespace upp::Objects {
    struct FMovieSceneEvaluationTreeNodeHandle {
        FEvaluationTreeEntryHandle ChildrenHandle;
        int Index;

        friend FArchive& operator>>(FArchive& Ar, FMovieSceneEvaluationTreeNodeHandle& Value);
    };
}