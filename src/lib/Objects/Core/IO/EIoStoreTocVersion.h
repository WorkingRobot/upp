#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class EIoStoreTocVersion : uint8_t {
        Invalid = 0,
        Initial,
        DirectoryIndex,
        PartitionSize,

        LatestPlusOne,
        Latest = LatestPlusOne - 1
    };
}