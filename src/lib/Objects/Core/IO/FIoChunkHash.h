#pragma once

#include "../Serialization/FArchive.h"

namespace upp::Objects {
	struct FIoChunkHash {
		char Hash[32];

		friend FArchive& operator>>(FArchive& Ar, FIoChunkHash& Value);
	};
}