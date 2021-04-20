#pragma once

#include "../Serialization/FArchive.h"

namespace upp::Objects {
    struct FIoFileIndexEntry {
        uint32_t Name;
        uint32_t NextFileEntry;
        uint32_t UserData;

        friend FArchive& operator>>(FArchive& Ar, FIoFileIndexEntry& Value);
    };
}