#include "FScriptObjectEntry.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FScriptObjectEntry& Value)
    {
        Ar >> Value.ObjectName;
        Ar >> Value.GlobalIndex;
        Ar >> Value.OuterIndex;
        Ar >> Value.CDOClassIndex;

        return Ar;
    }
}