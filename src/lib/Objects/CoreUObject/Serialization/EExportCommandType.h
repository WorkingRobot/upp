#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class EExportCommandType : uint32_t {
        Create,
        Serialize,
        Count,
    };
}