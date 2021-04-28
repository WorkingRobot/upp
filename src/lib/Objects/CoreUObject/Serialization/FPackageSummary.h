#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "../UObject/EPackageFlags.h"
#include "FMappedName.h"
#include "FPackageObjectIndex.h"

namespace upp::Objects {
    struct FPackageSummary {
		FMappedName Name;
		FMappedName SourceName;
		EPackageFlags PackageFlags;
		uint32_t CookedHeaderSize;
		int32_t NameMapNamesOffset;
		int32_t NameMapNamesSize;
		int32_t NameMapHashesOffset;
		int32_t NameMapHashesSize;
		int32_t ImportMapOffset;
		int32_t ExportMapOffset;
		int32_t ExportBundlesOffset;
		int32_t GraphDataOffset;
		int32_t GraphDataSize;

        friend FArchive& operator>>(FArchive& Ar, FPackageSummary& Value);
    };
}