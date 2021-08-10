#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "FAnimCurveType.h"
#include "FBoneReference.h"

namespace upp::Objects {
    struct FCurveMetaData {
        FAnimCurveType Type;
        std::vector<FBoneReference> LinkedBones;
        uint8_t MaxLOD;

        friend FArchive& operator>>(FArchive& Ar, FCurveMetaData& Value);
    };
}