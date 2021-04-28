#pragma once

#include "Name.h"

#include <vector>

namespace upp::Providers {
    struct Enum {
        Providers::Name& Name;
        std::vector<std::reference_wrapper<Providers::Name>> Names;
    };
}