#pragma once

#include "../../Core/IO/FIoContainerId.h"
#include "../../Core/Serialization/FArchive.h"
#include "../UObject/FPackageId.h"
#include "FPackageStoreEntry.h"

#include <unordered_map>

namespace upp::Objects {
    struct FContainerHeader {
        FIoContainerId ContainerId;
        uint32_t PackageCount;
        std::vector<uint8_t> Names;
        std::vector<uint8_t> NameHashes;
        std::unordered_map<FPackageId, FPackageStoreEntry> StoreEntries;
        std::vector<FPackageId> ImportedPackages;
        std::vector<std::pair<std::string, std::vector<std::pair<FPackageId, FPackageId>>>> CulturePackageMap; // FCulturePackageMap
        std::vector<std::pair<FPackageId, FPackageId>> PackageRedirects;

        friend FArchive& operator>>(FArchive& Ar, FContainerHeader& Value);
    };
}