#pragma once

#include "../../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FSimpleCurveKey {
        float Time;
        float Value;

        friend FArchive& operator>>(FArchive& Ar, FSimpleCurveKey& Value);
    };
}