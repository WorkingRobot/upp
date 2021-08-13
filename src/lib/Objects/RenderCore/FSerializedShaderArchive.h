#pragma once

#include "../Core/FileCache/FFileCachePreloadEntry.h"
#include "../Core/Misc/FSHAHash.h"
#include "../Core/Serialization/FArchive.h"
#include "FShaderMapEntry.h"
#include "FShaderCodeEntry.h"

namespace upp::Objects {
	struct FSerializedShaderArchive {
        std::vector<FSHAHash> ShaderMapHashes;
        std::vector<FSHAHash> ShaderHashes;
        std::vector<FShaderMapEntry> ShaderMapEntries;
        std::vector<FShaderCodeEntry> ShaderEntries;
        std::vector<FFileCachePreloadEntry> PreloadEntries;
        std::vector<uint32_t> ShaderIndices;

        friend FArchive& operator>>(FArchive& Ar, FSerializedShaderArchive& Value);
	};
}