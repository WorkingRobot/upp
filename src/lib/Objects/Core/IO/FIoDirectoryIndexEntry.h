#pragma once

#include "../Serialization/FArchive.h"

namespace upp::Objects {
    struct FIoDirectoryIndexEntry {
        uint32_t Name;
        uint32_t FirstChildEntry;
        uint32_t NextSiblingEntry;
        uint32_t FirstFileEntry;

        friend FArchive& operator>>(FArchive& Ar, FIoDirectoryIndexEntry& Value);
    };
}