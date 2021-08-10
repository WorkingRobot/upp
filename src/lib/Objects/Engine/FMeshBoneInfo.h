#pragma once

#include "../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FMeshBoneInfo {
        FName Name;
        int ParentIndex;

        friend FArchive& operator>>(FArchive& Ar, FMeshBoneInfo& Value);
    };
}