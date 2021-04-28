#include "FExportMapEntry.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FExportMapEntry& Value)
    {
		Ar >> Value.CookedSerialOffset;
		Ar >> Value.CookedSerialSize;
		Ar >> Value.ObjectName;
		Ar >> Value.OuterIndex;
		Ar >> Value.ClassIndex;
		Ar >> Value.SuperIndex;
		Ar >> Value.TemplateIndex;
		Ar >> Value.GlobalImportIndex;
		Ar >> Value.ObjectFlags;
		Ar >> Value.FilterFlags;
		Ar.Seek(3, ESeekDir::Cur);

        return Ar;
    }
}