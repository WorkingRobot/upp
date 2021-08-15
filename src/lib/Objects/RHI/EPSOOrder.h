#pragma once

#include <stdint.h>

namespace upp::Objects {
    // Internally FPiplelineFileCache::PSOOrder, but I moved it out to here
    enum class EPSOOrder : uint32_t {
        Default = 0, // Whatever order they are already in.
        FirstToLatestUsed = 1, // Start with the PSOs with the lowest first-frame used and work toward those with the highest.
        MostToLeastUsed = 2 // Start with the most often used PSOs working toward the least.
    };
}