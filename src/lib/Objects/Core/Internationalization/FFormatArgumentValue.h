#pragma once

#include "../Serialization/FArchive.h"
#include "FText.h"

#include <variant>

namespace upp::Objects {
    struct FFormatArgumentValue {
        std::variant<double, float, int64_t, uint64_t, FText> Value;

        friend FArchive& operator>>(FArchive& Ar, FFormatArgumentValue& Value);
    };
}