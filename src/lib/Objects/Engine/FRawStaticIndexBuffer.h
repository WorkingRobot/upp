#pragma once

#include "../Core/Math/FVector.h"
#include "../Core/Serialization/FArchive.h"

#include <variant>

namespace upp::Objects {
    struct FRawStaticIndexBuffer {
        std::variant<std::vector<uint32_t>, std::vector<uint16_t>> IndexStorage;

        friend FArchive& operator>>(FArchive& Ar, FRawStaticIndexBuffer& Value);
    };
}