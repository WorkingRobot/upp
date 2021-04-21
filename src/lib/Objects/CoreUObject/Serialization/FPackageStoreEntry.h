#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "../UObject/FPackageId.h"

namespace upp::Objects {
    struct FPackageStoreEntry {
		uint64_t ExportBundlesSize;
		int32_t ExportCount;
		int32_t ExportBundleCount;
		uint32_t LoadOrder;
		uint32_t Pad;
		uint32_t ImportedPackagesCount;
		uint32_t ImportedPackagesIdx;

        friend FArchive& operator>>(FArchive& Ar, FPackageStoreEntry& Value);
    };
}