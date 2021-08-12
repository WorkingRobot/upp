#pragma once

#include "PropertyData.h"

namespace upp::Providers {
    struct Property {
        Name& Name;
        uint16_t SchemaIdx;
        PropertyData Data;
    };
}