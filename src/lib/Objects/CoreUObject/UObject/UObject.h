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
        std::vector<FProperty> Properties;

        static std::unique_ptr<UObject> SerializeUnversioned(FArchive& Ar, const std::string& ClassName, FSerializeCtx& Ctx, bool IsCDO);

    protected:
        UObject(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO) : UObject(Ar, Schema, IsCDO) { }

        UObject(FArchive& Ar, const Providers::Schema& Schema, bool IsCDO);

        friend StructProperty;
    };
}