#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class EIoStoreTocEntryMetaFlags : uint8_t {
        None = 0x00,
        Compressed = 0x01,
        MemoryMapped = 0x02,
    };
}