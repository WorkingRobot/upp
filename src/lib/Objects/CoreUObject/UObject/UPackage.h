#pragma once

#include "UObject.h"

#include <vector>

namespace upp::Objects {
    struct UPackage {
        std::vector<std::unique_ptr<UObject>> Exports;
    };
}