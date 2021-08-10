#pragma once

#include "../../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FBoneReference {
        FName BoneName;

        friend FArchive& operator>>(FArchive& Ar, FBoneReference& Value);
    };
}