#pragma once

#include "../../Core/Serialization/FArchive.h"

#include "EExportCommandType.h"

namespace upp::Objects {
    struct FExportBundleEntry {
        uint32_t LocalExportIndex;
        EExportCommandType CommandType;

        friend FArchive& operator>>(FArchive& Ar, FExportBundleEntry& Value);
    };
}