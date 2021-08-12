#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "FMovieSceneEvaluationTree.h"
#include "TEvaluationTreeEntryContainer.h"

namespace upp::Objects {
    template<class T>
    struct TMovieSceneEvaluationTree : public FMovieSceneEvaluationTree {
        TEvaluationTreeEntryContainer<T> Data;

        friend FArchive& operator>>(FArchive& Ar, TMovieSceneEvaluationTree& Value)
        {
            Ar >> (FMovieSceneEvaluationTree&)Value;
            Ar >> Value.Data;

            return Ar;
        }
    };
}