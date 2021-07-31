#pragma once

#include "../Vfs/SmallMap.h"
#include "Enum.h"
#include "Schema.h"

#include <string>

namespace upp::Providers {
    class BaseProvider {
    protected:
        BaseProvider() = default;

    public:
        const Name* GetName(const std::string& Name) const;

        const Name* GetName(const char* Str, size_t StrSize) const;

        const Enum* GetEnum(const std::string& Name) const;

        const Schema* GetSchema(const std::string& Name) const;

    protected:
        Vfs::SmallMap<Name, Enum> Enums;
        Vfs::SmallMap<Name, Schema> Schemas;
        std::vector<Name> Names;
    };
}