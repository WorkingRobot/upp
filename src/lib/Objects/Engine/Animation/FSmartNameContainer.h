#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "FSmartNameMapping.h"

namespace upp::Objects {
    struct FSmartNameContainer {
        std::vector<std::pair<FName, FSmartNameMapping>> NameMappings;

        friend FArchive& operator>>(FArchive& Ar, FSmartNameContainer& Value);
    };
}