#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "FMovieSceneEvaluationTreeNode.h"
#include "TEvaluationTreeEntryContainer.h"

namespace upp::Objects {
    struct FMovieSceneEvaluationTree {
        FMovieSceneEvaluationTreeNode RootNode;
        TEvaluationTreeEntryContainer<FMovieSceneEvaluationTreeNode> ChildNodes;

        friend FArchive& operator>>(FArchive& Ar, FMovieSceneEvaluationTree& Value);
    };
}