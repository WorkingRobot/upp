#include "FIoDirectoryIndexEntry.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FIoDirectoryIndexEntry& Value)
    {
        Ar >> Value.Name;
        Ar >> Value.FirstChildEntry;
        Ar >> Value.NextSiblingEntry;
        Ar >> Value.FirstFileEntry;

        return Ar;
    }
}