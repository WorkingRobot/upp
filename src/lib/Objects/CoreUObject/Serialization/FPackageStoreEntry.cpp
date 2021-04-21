#include "FPackageStoreEntry.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FPackageStoreEntry& Value)
    {
        Ar >> Value.ExportBundlesSize;
        Ar >> Value.ExportCount;
        Ar >> Value.ExportBundleCount;
        Ar >> Value.LoadOrder;
        Ar >> Value.Pad;
        Ar >> Value.ImportedPackagesCount;
        Ar >> Value.ImportedPackagesIdx;

        return Ar;
    }
}