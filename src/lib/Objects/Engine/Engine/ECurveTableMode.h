#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class ECurveTableMode : uint8_t {
        Empty,
        SimpleCurves,
        RichCurves
    };
}