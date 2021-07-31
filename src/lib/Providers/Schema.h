#pragma once

#include "Property.h"

#include <vector>

namespace upp::Providers {
    struct Schema {
        Providers::Name& Name;
        const Schema* SuperType;
        uint16_t PropCount;
        std::vector<Property> Properties;
    };
}