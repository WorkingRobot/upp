#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "FPrecomputedVisibilityCell.h"
#include "FCompressedVisibilityChunk.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/833b26ffdf07619e3ce07d08a0820e8e18ae2f1a/Engine/Source/Runtime/Engine/Classes/Engine/Level.h#L200
    struct FPrecomputedVisibilityBucket {
        int CellDataSize;
        std::vector<FPrecomputedVisibilityCell> Cells;
        std::vector<FCompressedVisibilityChunk> CellDataChunks;

        friend FArchive& operator>>(FArchive& Ar, FPrecomputedVisibilityBucket& Value);
    };
}