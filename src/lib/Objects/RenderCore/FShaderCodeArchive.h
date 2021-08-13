#pragma once

#include "../Core/Serialization/FArchive.h"
#include "FSerializedShaderArchive.h"

namespace upp::Objects {
	struct FShaderCodeArchive {
        uint32_t ArchiveVersion;
        FSerializedShaderArchive SerializedShaders;
        std::vector<std::vector<uint8_t>> ShaderCode;

        FShaderCodeArchive(FArchive& Ar);
        friend FArchive& operator>>(FArchive& Ar, FShaderCodeArchive& Value);
	};
}