#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "FMappedName.h"
#include "FPackageObjectIndex.h"

namespace upp::Objects {
    struct FScriptObjectEntry {
        FMappedName ObjectName;
        FPackageObjectIndex GlobalIndex;
        FPackageObjectIndex OuterIndex;
        FPackageObjectIndex CDOClassIndex;

        friend FArchive& operator>>(FArchive& Ar, FScriptObjectEntry& Value);
    };
}