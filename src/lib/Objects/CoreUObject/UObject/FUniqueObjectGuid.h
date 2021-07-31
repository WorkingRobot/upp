#pragma once

#include "../../Core/Misc/FGuid.h"
#include "../../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FUniqueObjectGuid : public FGuid {
        using FGuid::FGuid;

        friend FArchive& operator>>(FArchive& Ar, FUniqueObjectGuid& Value);
    };
}