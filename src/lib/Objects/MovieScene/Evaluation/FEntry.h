#pragma once

#include "../../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FEntry {
        int StartIndex;
        int Size;
        int Capacity;

        friend FArchive& operator>>(FArchive& Ar, FEntry& Value);
    };
}