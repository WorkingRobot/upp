#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "FEntityAndMetaDataIndex.h"
#include "TMovieSceneEvaluationTree.h"

namespace upp::Objects {
    struct FMovieSceneEvaluationFieldEntityTree {
        TMovieSceneEvaluationTree<FEntityAndMetaDataIndex> SerializedData;

        friend FArchive& operator>>(FArchive& Ar, FMovieSceneEvaluationFieldEntityTree& Value);
    };
}