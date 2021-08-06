#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class EBspNodeFlags : uint8_t {
        NF_NotCsg = 0x01, // Node is not a Csg splitter, i.e. is a transparent poly.
        NF_NotVisBlocking = 0x04, // Node does not block visibility, i.e. is an invisible collision hull.
        NF_BrightCorners = 0x10, // Temporary.
        NF_IsNew = 0x20, // Editor: Node was newly-added.
        NF_IsFront = 0x40, // Filter operation bounding-sphere precomputed and guaranteed to be front.
        NF_IsBack = 0x80, // Guaranteed back.
    };
}