#pragma once

#include "../Core/Serialization/FArchive.h"

namespace upp::Objects {
	struct FShaderMapEntry {
        uint32_t ShaderIndicesOffset;
        uint32_t NumShaders;
        uint32_t FirstPreloadIndex;
        uint32_t NumPreloadEntries;

        friend FArchive& operator>>(FArchive& Ar, FShaderMapEntry& Value);
	};
}