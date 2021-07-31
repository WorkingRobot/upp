#pragma once

#include "../../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FFieldPath {
        std::vector<std::string> Names;

        friend FArchive& operator>>(FArchive& Ar, FFieldPath& Value);
    };
}