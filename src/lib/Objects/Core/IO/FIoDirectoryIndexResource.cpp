#include "FIoDirectoryIndexResource.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FIoDirectoryIndexResource& Value)
    {
        Ar >> Value.MountPoint;
        Ar >> Value.DirectoryEntries;
        Ar >> Value.FileEntries;
        Ar >> Value.StringTable;

        return Ar;
    }
}