#pragma once

#include "../../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FMappedName {
        uint32_t Index;
        uint32_t Number;

        friend FArchive& operator>>(FArchive& Ar, FMappedName& Value);
    };
}