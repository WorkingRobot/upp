#include "FIoFileIndexEntry.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FIoFileIndexEntry& Value)
    {
        Ar >> Value.Name;
        Ar >> Value.NextFileEntry;
        Ar >> Value.UserData;

        return Ar;
    }
}