#pragma once

#include "../../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FEntityAndMetaDataIndex {
        int EntityIndex;
        int MetaDataIndex;

        friend FArchive& operator>>(FArchive& Ar, FEntityAndMetaDataIndex& Value);
    };
}