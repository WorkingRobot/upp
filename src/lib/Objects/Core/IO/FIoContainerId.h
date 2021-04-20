#pragma once

#include "../Serialization/FArchive.h"

namespace upp::Objects {
    struct FIoContainerId {
        uint64_t Id;

        friend FArchive& operator>>(FArchive& Ar, FIoContainerId& Value);
    };
}