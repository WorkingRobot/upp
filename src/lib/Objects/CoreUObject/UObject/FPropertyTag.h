#pragma once

#include "../../../Providers/Property.h"
#include "../../Core/Misc/FGuid.h"

namespace upp::Objects {
    struct FPropertyTag {
        FPropertyTag(const Providers::Property& PropertyInfo);
        FPropertyTag(const Providers::PropertyData& PropertyData);

        std::string Name;
        Providers::PropertyData TagData;
    };
}