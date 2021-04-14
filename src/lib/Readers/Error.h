#pragma once

#include <stdint.h>

namespace upp::Readers {
    enum class Error : int32_t {
        None,
        InvalidFooter,
        UnsupportedFrozenIndex,
        InvalidAesKey,
        InvalidIndexHash,
        MissingFullDirectoryIndex
    };
}