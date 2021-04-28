#include "FPackageSummary.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FPackageSummary& Value)
    {
		Ar >> Value.Name;
		Ar >> Value.SourceName;
		Ar >> Value.PackageFlags;
		Ar >> Value.CookedHeaderSize;
		Ar >> Value.NameMapNamesOffset;
		Ar >> Value.NameMapNamesSize;
		Ar >> Value.NameMapHashesOffset;
		Ar >> Value.NameMapHashesSize;
		Ar >> Value.ImportMapOffset;
		Ar >> Value.ExportMapOffset;
		Ar >> Value.ExportBundlesOffset;
		Ar >> Value.GraphDataOffset;
		Ar >> Value.GraphDataSize;
		// Just padding
		Ar.Seek(4, ESeekDir::Cur);

		return Ar;
    }
}