#pragma once

#include "../../Core/Serialization/FArchive.h"

namespace upp::Vfs {
    class Vfs;
}

namespace upp::Objects {
    struct UObject {
        std::string ObjectName;

        std::string ClassName;

        static std::unique_ptr<UObject> SerializeUnversioned(FArchive& Ar, const std::string& ClassName, Vfs::Vfs& Vfs);
    };
}