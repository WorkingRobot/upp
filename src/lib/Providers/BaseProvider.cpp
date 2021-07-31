#include "BaseProvider.h"

namespace upp::Providers {
    const Name* BaseProvider::GetName(const std::string& Name) const
    {
        return GetName(Name.c_str(), Name.size());
    }

    const Name* BaseProvider::GetName(const char* Str, size_t StrSize) const
    {
        auto Itr = std::find_if(Names.begin(), Names.end(), [Str, StrSize](const Name& Name) {
            return Name.compare(Str, StrSize);
        });

        if (Itr != Names.end()) {
            return &*Itr;
        }
        return nullptr;
    }

    const Enum* BaseProvider::GetEnum(const std::string& Name) const
    {
        auto Itr = Enums.SearchValues(Name.c_str(), Name.size());
        
        if (Itr != Enums.end()) {
            return &Itr->second;
        }
        return nullptr;
    }

    const Schema* BaseProvider::GetSchema(const std::string& Name) const
    {
        auto Itr = Schemas.SearchValues(Name.c_str(), Name.size());

        if (Itr != Schemas.end()) {
            return &Itr->second;
        }
        return nullptr;
    }
}