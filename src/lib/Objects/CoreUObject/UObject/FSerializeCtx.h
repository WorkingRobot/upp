#pragma once

#include "../../Core/Serialization/FArchive.h"

namespace upp::Vfs {
    class Vfs;
}

namespace upp::Objects {
    struct FSerializeCtx {
    public:
        FSerializeCtx(Vfs::Vfs& Vfs, const std::string& PackageName);

        Vfs::Vfs& GetVfs();

        std::unique_ptr<FArchive> GetSiblingArchive(const char* Extension);

    private:
        Vfs::Vfs& Vfs;
        std::string PackageName;
    };
}