#include "FContainerHeader.h"

#include "../../Core/Serialization/FByteArchive.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FContainerHeader& Value)
    {
        Ar >> Value.ContainerId;
        Ar >> Value.PackageCount;
        Ar >> Value.Names;
        Ar >> Value.NameHashes;
        Ar >> Value.PackageIds;
        
        int StoreEntriesByteCount;
        Ar >> StoreEntriesByteCount;

        Ar.ReadBuffer(Value.StoreEntries, Value.PackageCount);
        Ar.ReadBuffer(Value.ImportedPackages, StoreEntriesByteCount - Value.PackageCount * sizeof(FPackageStoreEntry) / sizeof(FPackageId));

        for (uint32_t Idx = 0; Idx < Value.PackageCount; ++Idx) {
            if (Value.StoreEntries[Idx].ImportedPackagesCount != 0) {
                Value.StoreEntries[Idx].ImportedPackagesIdx -= (Value.PackageCount - Idx) * sizeof(FPackageStoreEntry) - 24;
                Value.StoreEntries[Idx].ImportedPackagesIdx /= sizeof(FPackageId);
            }
        }

        Ar >> Value.CulturePackageMap;
        Ar >> Value.PackageRedirects;

        return Ar;
    }
}