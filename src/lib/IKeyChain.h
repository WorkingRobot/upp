#pragma once

#include "Objects/Core/Misc/FAESSchedule.h"
#include "Objects/Core/Misc/FGuid.h"

namespace upp {
    class IKeyChain {
    public:
        virtual const Objects::FAESSchedule& GetKey(const Objects::FGuid& Guid) const = 0;
    };
}