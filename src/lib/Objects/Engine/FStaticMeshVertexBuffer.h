#pragma once

#include "../Core/Math/FVector2D.h"
#include "../Core/Math/FVector2DHalf.h"
#include "../Core/Serialization/FArchive.h"
#include "../RenderCore/FPackedNormal.h"
#include "../RenderCore/FPackedRGBA16N.h"

#include <variant>

namespace upp::Objects {
    struct FStaticMeshVertexBuffer {
        uint32_t NumTexCoords;
        uint32_t NumVertices;
        std::variant<std::vector<std::pair<FPackedNormal, FPackedNormal>>, std::vector<std::pair<FPackedRGBA16N, FPackedRGBA16N>>> TangentsData;
        std::variant<std::vector<FVector2DHalf>, std::vector<FVector2D>> TexcoordData;

        friend FArchive& operator>>(FArchive& Ar, FStaticMeshVertexBuffer& Value);
    };
}