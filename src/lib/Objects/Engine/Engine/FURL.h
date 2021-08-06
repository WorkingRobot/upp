#pragma once

#include "../../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FURL {
        std::string Protocol;
        std::string Host;
        std::string Map;
        std::string Portal;
        std::vector<std::string> Op;
        int Port;
        int Valid;

        friend FArchive& operator>>(FArchive& Ar, FURL& Value);
    };
}