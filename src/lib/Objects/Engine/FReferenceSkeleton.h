#pragma once

#include "../Core/Math/FTransform.h"
#include "../Core/Serialization/FArchive.h"
#include "FMeshBoneInfo.h"

namespace upp::Objects {
    struct FReferenceSkeleton {
        std::vector<FMeshBoneInfo> RefBoneInfo;
        std::vector<FTransform> RefBonePose;
        std::vector<std::pair<FName, int>> NameToIndexMap;

        friend FArchive& operator>>(FArchive& Ar, FReferenceSkeleton& Value);
    };
}