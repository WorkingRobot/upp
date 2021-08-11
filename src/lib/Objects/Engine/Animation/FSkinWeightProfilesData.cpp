#include "FSkinWeightProfilesData.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FSkinWeightProfilesData& Value)
    {
        Ar >> Value.OverrideData;

        return Ar;
    }
}