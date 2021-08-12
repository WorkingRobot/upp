#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "../../CoreUObject/UObject/FSerializeCtx.h"
#include "../../CoreUObject/UObject/UObject.h"

namespace upp::Objects {
    struct FMovieSceneEvalTemplatePtr {
        std::optional<UObject> Data;

        void Serialize(FArchive& Ar, FSerializeCtx& Ctx);
    };
}