#pragma once

#include "../../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FPackageId {
        uint64_t Id;

        friend FArchive& operator>>(FArchive& Ar, FPackageId& Value);
    };
}