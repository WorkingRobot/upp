#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "FIndexLengthPair.h"

namespace upp::Objects {
    struct FDuplicatedVerticesBuffer {
        std::vector<uint32_t> DupVertData;
        std::vector<FIndexLengthPair> DupVertIndexData;

        friend FArchive& operator>>(FArchive& Ar, FDuplicatedVerticesBuffer& Value);
    };
}