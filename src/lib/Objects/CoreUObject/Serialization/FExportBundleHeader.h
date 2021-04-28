#pragma once

#include "../../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FExportBundleHeader {
        uint32_t FirstEntryIndex;
        uint32_t EntryCount;

        friend FArchive& operator>>(FArchive& Ar, FExportBundleHeader& Value);
    };
}