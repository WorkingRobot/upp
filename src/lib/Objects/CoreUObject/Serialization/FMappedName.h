#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "EMappedNameType.h"

namespace upp::Objects {
    struct FMappedName {
        uint32_t Index;
        uint32_t Number;

        friend FArchive& operator>>(FArchive& Ar, FMappedName& Value);

        bool IsValid() const;

        EMappedNameType GetType() const;

        bool IsGlobal() const;

        uint32_t GetIndex() const;

        uint32_t GetNumber() const;
    };
}