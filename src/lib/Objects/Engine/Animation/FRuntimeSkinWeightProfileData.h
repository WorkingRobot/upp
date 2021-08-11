#pragma once

#include "../../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FRuntimeSkinWeightProfileData {
        std::vector<uint8_t> BoneIDs;
        std::vector<uint8_t> BoneWeights;
        uint8_t NumWeightsPerVertex;
        std::vector<std::pair<uint32_t, uint32_t>> VertexIndexToInfluenceOffset;

        friend FArchive& operator>>(FArchive& Ar, FRuntimeSkinWeightProfileData& Value);
    };
}