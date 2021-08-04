#pragma once

#include "../../../Providers/Schema.h"
#include "../../Core/Serialization/FArchive.h"
#include "FProperty.h"
#include "FSerializeCtx.h"

namespace upp::Vfs {
    class Vfs;
}

namespace upp::Objects {
    struct UObject {
        const Providers::Schema& Schema;
        std::vector<std::pair<uint32_t, FProperty>> Properties;

        UObject(FArchive& Ar, const Providers::Schema& Schema, bool IsCDO = true);

        virtual ~UObject() = default;

        const FProperty* GetProperty(uint32_t SchemaIdx) const;

        const FProperty* GetProperty(const std::string& Name) const;

        template<class T>
        const T* Get(const std::string& Name) const
        {
            auto Prop = GetProperty(Name);
            return Prop ? Prop->Get<T>() : nullptr;
        }

        static std::unique_ptr<UObject> SerializeUnversioned(FArchive& Ar, const std::string& ClassName, FSerializeCtx& Ctx, bool IsCDO);

    protected:
        UObject(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO) : UObject(Ar, Schema, IsCDO) { }
    };
}