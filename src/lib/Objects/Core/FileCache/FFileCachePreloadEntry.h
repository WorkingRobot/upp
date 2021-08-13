#pragma once

#include "../Serialization/FArchive.h"

namespace upp::Objects {
	struct FFileCachePreloadEntry {
        int64_t Offset;
        int64_t Size;

        friend FArchive& operator>>(FArchive& Ar, FFileCachePreloadEntry& Value);
	};
}