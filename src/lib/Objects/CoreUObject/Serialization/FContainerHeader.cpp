#include "FContainerHeader.h"

#include "../../Core/Serialization/FByteArchive.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FContainerHeader& Value)
    {
        Ar >> Value.ContainerId;
        Ar >> Value.PackageCount;
        Ar >> Value.Names;
        Ar >> Value.NameHashes;

        std::vector<FPackageId> PackageIds;
        Ar >> PackageIds;
        
        int StoreEntriesByteCount;
        Ar >> StoreEntriesByteCount;

        std::vector<FPackageStoreEntry> StoreEntries;
        Ar.ReadBuffer(StoreEntries, Value.PackageCount);
        Ar.ReadBuffer(Value.ImportedPackages, (StoreEntriesByteCount - Value.PackageCount * sizeof(FPackageStoreEntry)) / sizeof(FPackageId));

        Value.StoreEntries.reserve(Value.PackageCount);
        for (uint32_t Idx = 0; Idx < Value.PackageCount; ++Idx) {
            auto& StoreEntry = Value.StoreEntries.emplace(PackageIds[Idx], StoreEntries[Idx]).first->second;

            if (StoreEntry.ImportedPackagesCount > 0) {
                StoreEntry.ImportedPackagesIdx -= (Value.PackageCount - Idx) * sizeof(FPackageStoreEntry) - 24;
                StoreEntry.ImportedPackagesIdx /= sizeof(FPackageId);
            }
        }

        Ar >> Value.CulturePackageMap;
        Ar >> Value.PackageRedirects;

        return Ar;
    }
}