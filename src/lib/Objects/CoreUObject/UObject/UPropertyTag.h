#pragma once

#include "../../../Providers/Property.h"
#include "../../Core/Misc/FGuid.h"

namespace upp::Objects {
    struct UPropertyTag {
        UPropertyTag(const Providers::Property& PropertyInfo);
        UPropertyTag(const Providers::PropertyData& PropertyData);

        const Providers::PropertyData& TagData;
    };
}