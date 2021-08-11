#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "FRuntimeSkinWeightProfileData.h"

namespace upp::Objects {
    struct FSkinWeightProfilesData {
        std::vector<std::pair<FName, FRuntimeSkinWeightProfileData>> OverrideData;

        friend FArchive& operator>>(FArchive& Ar, FSkinWeightProfilesData& Value);
    };
}