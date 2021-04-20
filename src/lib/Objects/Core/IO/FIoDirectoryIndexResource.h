#pragma once

#include "../Serialization/FArchive.h"
#include "FIoDirectoryIndexEntry.h"
#include "FIoFileIndexEntry.h"

namespace upp::Objects {
    struct FIoDirectoryIndexResource {
        std::string MountPoint;
        std::vector<FIoDirectoryIndexEntry> DirectoryEntries;
        std::vector<FIoFileIndexEntry> FileEntries;
        std::vector<std::string> StringTable;

        friend FArchive& operator>>(FArchive& Ar, FIoDirectoryIndexResource& Value);
    };
}