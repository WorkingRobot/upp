#include "FNumberFormattingOptions.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FNumberFormattingOptions& Value)
    {
        Ar >> Value.AlwaysSign;
        Ar >> Value.UseGrouping;
        Ar >> Value.RoundingMode;
        Ar >> Value.MinimumIntegralDigits;
        Ar >> Value.MaximumIntegralDigits;
        Ar >> Value.MinimumFractionalDigits;
        Ar >> Value.MaximumFractionalDigits;

        return Ar;
    }
}