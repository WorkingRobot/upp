#pragma once

#include "../Serialization/FArchive.h"
#include "ERoundingMode.h"

namespace upp::Objects {
    struct FNumberFormattingOptions {
        bool AlwaysSign;
        bool UseGrouping;
        ERoundingMode RoundingMode;
        int MinimumIntegralDigits;
        int MaximumIntegralDigits;
        int MinimumFractionalDigits;
        int MaximumFractionalDigits;

        friend FArchive& operator>>(FArchive& Ar, FNumberFormattingOptions& Value);
    };
}