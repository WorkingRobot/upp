#include "FPrecomputedVolumeDistanceField.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FPrecomputedVolumeDistanceField& Value)
    {
        Ar >> Value.VolumeMaxDistance;
        Ar >> Value.VolumeBox;
        Ar >> Value.VolumeSizeX;
        Ar >> Value.VolumeSizeY;
        Ar >> Value.VolumeSizeZ;
        Ar >> Value.Data;

        return Ar;
    }
}