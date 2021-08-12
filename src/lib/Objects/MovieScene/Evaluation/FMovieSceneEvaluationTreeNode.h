#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "../../Core/Math/TRange.h"
#include "../../Core/Misc/FFrameNumber.h"
#include "FEvaluationTreeEntryHandle.h"
#include "FMovieSceneEvaluationTreeNodeHandle.h"

namespace upp::Objects {
    struct FMovieSceneEvaluationTreeNode {
        TRange<FFrameNumber> Range;
        FMovieSceneEvaluationTreeNodeHandle Parent;
        FEvaluationTreeEntryHandle ChildrenID;
        FEvaluationTreeEntryHandle DataID;

        friend FArchive& operator>>(FArchive& Ar, FMovieSceneEvaluationTreeNode& Value);
    };
}