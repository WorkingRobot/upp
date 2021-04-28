#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "../UObject/EObjectFlags.h"
#include "EExportFilterFlags.h"
#include "FMappedName.h"
#include "FPackageObjectIndex.h"

namespace upp::Objects {
    struct FExportMapEntry {
		uint64_t CookedSerialOffset;
		uint64_t CookedSerialSize;
		FMappedName ObjectName;
		FPackageObjectIndex OuterIndex;
		FPackageObjectIndex ClassIndex;
		FPackageObjectIndex SuperIndex;
		FPackageObjectIndex TemplateIndex;
		FPackageObjectIndex GlobalImportIndex;
		EObjectFlags ObjectFlags;
		EExportFilterFlags FilterFlags;
		uint8_t Padding[3];

        friend FArchive& operator>>(FArchive& Ar, FExportMapEntry& Value);
    };
}