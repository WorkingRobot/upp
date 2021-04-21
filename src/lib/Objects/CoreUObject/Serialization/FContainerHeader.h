#pragma once

#include "../../Core/IO/FIoContainerId.h"
#include "../../Core/Serialization/FArchive.h"
#include "../UObject/FPackageId.h"
#include "FPackageStoreEntry.h"

namespace upp::Objects {
    struct FContainerHeader {
        FIoContainerId ContainerId;
        uint32_t PackageCount;
        std::vector<uint8_t> Names;
        std::vector<uint8_t> NameHashes;
        std::vector<FPackageId> PackageIds;
        std::vector<FPackageStoreEntry> StoreEntries; //FPackageStoreEntry[PackageCount]
        std::vector<FPackageId> ImportedPackages;
        std::vector<std::pair<std::string, std::vector<std::pair<FPackageId, FPackageId>>>> CulturePackageMap; // FCulturePackageMap
        std::vector<std::pair<FPackageId, FPackageId>> PackageRedirects;

        friend FArchive& operator>>(FArchive& Ar, FContainerHeader& Value);
    };
}