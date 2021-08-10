#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "FPackageIndex.h"

namespace upp::Objects {
    struct FFieldPath {
        std::vector<FName> Path;
        FPackageIndex ResolvedOwner;

        friend FArchive& operator>>(FArchive& Ar, FFieldPath& Value);
    };
}