#pragma once

#include "../Core/Serialization/FArchive.h"
#include "EVertexElementType.h"

#include <compare>

namespace upp::Objects {
    struct FVertexElement {
        uint8_t StreamIndex;
        uint8_t Offset;
        EVertexElementType Type;
        uint8_t AttributeIndex;
        uint16_t Stride;
        uint16_t bUseInstanceIndex;

        friend FArchive& operator>>(FArchive& Ar, FVertexElement& Value);

        std::strong_ordering operator<=>(const FVertexElement& Other) const {
            if (auto Ret = StreamIndex <=> Other.StreamIndex; Ret != 0)
                return Ret;
            if (auto Ret = Offset <=> Other.Offset; Ret != 0)
                return Ret;
            return AttributeIndex <=> Other.AttributeIndex;
        }
    };
}