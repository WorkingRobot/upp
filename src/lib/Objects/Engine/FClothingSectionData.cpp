#include "FClothingSectionData.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FClothingSectionData& Value)
    {
        Ar >> Value.AssetGuid;
        Ar >> Value.AssetLodIndex;

        return Ar;
    }
}