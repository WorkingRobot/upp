#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "../FMeshToMeshVertData.h"

namespace upp::Objects {
    struct FSkeletalMeshVertexClothBuffer {
        std::vector<FMeshToMeshVertData> VertexData;
        std::vector<std::pair<uint32_t, uint32_t>> ClothIndexMapping;

        friend FArchive& operator>>(FArchive& Ar, FSkeletalMeshVertexClothBuffer& Value);
    };
}