#pragma once

#include "../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FExpressionInput {
        int OutputIndex;
        FName InputName;
        FName ExpressionName;

        friend FArchive& operator>>(FArchive& Ar, FExpressionInput& Value);
    };
}