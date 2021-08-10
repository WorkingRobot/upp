#pragma once

#include "../../Core/Math/FTransform.h"
#include "../../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FReferencePose {
        FName PoseName;
        std::vector<FTransform> ReferencePose;

        friend FArchive& operator>>(FArchive& Ar, FReferencePose& Value);
    };
}