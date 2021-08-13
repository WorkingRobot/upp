#pragma once

#include "../Core/Serialization/FArchive.h"
#include "../RHI/EShaderFrequency.h"

namespace upp::Objects {
	struct FShaderCodeEntry {
        uint64_t Offset;
        uint32_t Size;
        uint32_t UncompressedSize;
        EShaderFrequency Frequency;

        friend FArchive& operator>>(FArchive& Ar, FShaderCodeEntry& Value);
	};
}