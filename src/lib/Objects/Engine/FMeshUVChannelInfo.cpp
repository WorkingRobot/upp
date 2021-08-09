#include "FMeshUVChannelInfo.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FMeshUVChannelInfo& Value)
    {
        int bInitialized;
        Ar >> bInitialized;
        Value.Initialized = bInitialized;
        int bOverrideDensities;
        Ar >> bOverrideDensities;
        Value.OverrideDensities = bOverrideDensities;
        Ar >> Value.LocalUVDensities;

        return Ar;
    }
}