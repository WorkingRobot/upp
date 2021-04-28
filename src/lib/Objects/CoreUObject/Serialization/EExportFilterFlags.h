#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class EExportFilterFlags : uint8_t {
        None,
        NotForClient,
        NotForServer
    };
}