#pragma once

#include "../../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FAnimCurveType {
        bool Material;
        bool MorphTarget;

        friend FArchive& operator>>(FArchive& Ar, FAnimCurveType& Value);
    };
}