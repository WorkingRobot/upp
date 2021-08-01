#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "EPackageObjectIndexType.h"

namespace upp::Objects {
    struct FPackageObjectIndex {
        uint64_t TypeAndId;

        friend FArchive& operator>>(FArchive& Ar, FPackageObjectIndex& Value);

        bool IsValid() const;

        bool IsExport() const;

        bool IsImport() const;

        bool IsScriptImport() const;

        bool IsPackageImport() const;

        EPackageObjectIndexType GetType() const;

        uint64_t GetValue() const;

        friend auto operator<=>(const FPackageObjectIndex&, const FPackageObjectIndex&) = default;
    };
}

namespace std {
    template<> struct hash<upp::Objects::FPackageObjectIndex>
    {
        std::size_t operator()(upp::Objects::FPackageObjectIndex const& s) const noexcept
        {
            return s.TypeAndId;
        }
    };
}