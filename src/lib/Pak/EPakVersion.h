#pragma once

#include <stdint.h>

namespace upp::Pak {
    enum class EPakVersion : int32_t {
        Initial = 1,
		NoTimestamps = 2,
		CompressionEncryption = 3,
		IndexEncryption = 4,
		RelativeChunkOffsets = 5,
		DeleteRecords = 6,
		EncryptionKeyGuid = 7,
		FNameBasedCompressionMethod = 8,
		FrozenIndex = 9,
		PathHashIndex = 10,
		Fnv64BugFix = 11,

		LatestPlusOne,
		Invalid,
		Latest = LatestPlusOne - 1
    };
}