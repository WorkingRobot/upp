#pragma once

#include "../Serialization/FArchive.h"

namespace upp::Objects {
    struct FIoContainerId {
        uint64_t Id;

        bool IsValid() const {
            return Id != -1;
        }

        friend FArchive& operator>>(FArchive& Ar, FIoContainerId& Value);
    };
}