#pragma once

#include "../../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FPackageObjectIndex {
        uint64_t TypeAndId;

        friend FArchive& operator>>(FArchive& Ar, FPackageObjectIndex& Value);
    };
}