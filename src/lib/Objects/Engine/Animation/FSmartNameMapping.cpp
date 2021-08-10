#include "FSmartNameMapping.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FSmartNameMapping& Value)
    {
        Ar >> Value.CurveMetaDataMap;

        return Ar;
    }
}