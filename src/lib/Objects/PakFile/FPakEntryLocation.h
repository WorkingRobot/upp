#pragma once

#include "../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FPakEntryLocation {
        static constexpr int32_t Invalid = std::numeric_limits<int32_t>::min();
        static constexpr int32_t MaxIndex = std::numeric_limits<int32_t>::max() - 1;

        int32_t Index;

        constexpr FPakEntryLocation() :
            Index(Invalid)
        {

        }

        friend FArchive& operator>>(FArchive& Ar, FPakEntryLocation& Value)
        {
            Ar >> Value.Index;

            return Ar;
        }
    };
}