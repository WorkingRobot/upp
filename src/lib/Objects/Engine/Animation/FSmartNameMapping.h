#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "FCurveMetaData.h"

namespace upp::Objects {
    struct FSmartNameMapping {
        std::vector<std::pair<FName, FCurveMetaData>> CurveMetaDataMap;

        friend FArchive& operator>>(FArchive& Ar, FSmartNameMapping& Value);
    };
}