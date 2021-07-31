#pragma once

#include "../../../Providers/Schema.h"
#include "../../Core/Serialization/FArchive.h"
#include "FProperty.h"

namespace upp::Vfs {
    class Vfs;
}

namespace upp::Objects {
    struct UObject {
        std::vector<FProperty> Properties;

        static std::unique_ptr<UObject> SerializeUnversioned(FArchive& Ar, const std::string& ClassName, Vfs::Vfs& Vfs);

    protected:
        UObject(FArchive& Ar, const Providers::Schema& Schema);

        friend StructProperty;
    };
}