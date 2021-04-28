#include "FExportBundleEntry.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FExportBundleEntry& Value)
    {
        Ar >> Value.LocalExportIndex;
        Ar >> Value.CommandType;

        return Ar;
    }
}