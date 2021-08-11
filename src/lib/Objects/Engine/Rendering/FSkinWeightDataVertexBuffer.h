#pragma once

#include "../../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FSkinWeightDataVertexBuffer {
        bool VariableBonesPerVertex;
        uint32_t MaxBoneInfluences;
        uint32_t NumBones;
        uint32_t NumVertices;
        bool Use16BitBoneIndex;
        std::vector<uint8_t> WeightData;

        friend FArchive& operator>>(FArchive& Ar, FSkinWeightDataVertexBuffer& Value);
    };
}