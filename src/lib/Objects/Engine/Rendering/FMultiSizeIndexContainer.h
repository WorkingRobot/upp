#pragma once

#include "../../Core/Serialization/FArchive.h"

#include <variant>

namespace upp::Objects {
    struct FMultiSizeIndexContainer {
        std::variant<std::vector<uint32_t>, std::vector<uint16_t>> IndexStorage;

        friend FArchive& operator>>(FArchive& Ar, FMultiSizeIndexContainer& Value);
    };
}