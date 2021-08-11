#include "FSkeletalMaterial.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FSkeletalMaterial& Value)
    {
        Ar >> Value.MaterialInterface;
        Ar >> Value.MaterialSlotName;

        int bSerializeImportedMaterialSlotName;
        Ar >> bSerializeImportedMaterialSlotName;
        if (bSerializeImportedMaterialSlotName) {
            Ar >> Value.ImportedMaterialSlotName;
        }

        Ar >> Value.UVChannelData;

        return Ar;
    }
}