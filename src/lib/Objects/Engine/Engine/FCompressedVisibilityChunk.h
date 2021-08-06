#pragma once

#include "../../Core/Serialization/FArchive.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/833b26ffdf07619e3ce07d08a0820e8e18ae2f1a/Engine/Source/Runtime/Engine/Classes/Engine/Level.h#L180
    struct FCompressedVisibilityChunk {
        bool IsCompressed;
        int UncompressedSize;
        std::vector<uint8_t> Data;

        friend FArchive& operator>>(FArchive& Ar, FCompressedVisibilityChunk& Value);
    };
}