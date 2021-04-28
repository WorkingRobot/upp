#include "FExportBundleHeader.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FExportBundleHeader& Value)
    {
        Ar >> Value.FirstEntryIndex;
        Ar >> Value.EntryCount;

        return Ar;
    }
}