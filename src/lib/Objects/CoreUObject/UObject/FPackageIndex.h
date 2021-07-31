#pragma once

#include "../../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FPackageIndex {
        FPackageIndex(int32_t Idx = 0);

        int32_t Idx;

        friend FArchive& operator>>(FArchive& Ar, FPackageIndex& Value);

        bool IsValid() const;

        bool IsExport() const;

        bool IsImport() const;

        uint32_t GetValue() const;
    };
}