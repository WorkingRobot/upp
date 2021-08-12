#pragma once

#include "../../../Providers/Schema.h"
#include "../../Core/Serialization/FArchive.h"
#include "UProperty.h"
#include "FSerializeCtx.h"

namespace upp::Vfs {
    class Vfs;
}

namespace upp::Objects {
    struct UObject {
        const Providers::Schema& Schema;
        std::vector<std::pair<uint32_t, UProperty>> Properties;

        UObject(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO = true);

        virtual ~UObject() = default;

        const UProperty* GetProperty(uint32_t SchemaIdx) const;

        const UProperty* GetProperty(const std::string& Name) const;

        template<class T>
        const T* Get(const std::string& Name) const
        {
            auto Prop = GetProperty(Name);
            return Prop ? Prop->Get<T>() : nullptr;
        }

        static std::unique_ptr<UObject> SerializeUnversioned(FArchive& Ar, const std::string& ClassName, FSerializeCtx& Ctx, bool IsCDO);
    };
}