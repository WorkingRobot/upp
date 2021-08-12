#pragma once

#include "../../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FPackageId {
        uint64_t Id;

        friend FArchive& operator>>(FArchive& Ar, FPackageId& Value);

        friend auto operator<=>(const FPackageId&, const FPackageId&) = default;
    };
}

namespace std {
    template<>
    struct hash<upp::Objects::FPackageId>
    {
        std::size_t operator()(upp::Objects::FPackageId const& s) const noexcept
        {
            return std::hash<uint64_t>{}(s.Id);
        }
    };
}