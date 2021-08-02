#include "FSerializeCtx.h"

#include "../../../Vfs/Vfs.h"

namespace upp::Objects {
    FSerializeCtx::FSerializeCtx(Vfs::Vfs& Vfs, const std::string& PackageName) :
        Vfs(Vfs),
        PackageName(PackageName + ".")
    {

    }

    Vfs::Vfs& FSerializeCtx::GetVfs()
    {
        return Vfs;
    }

    std::unique_ptr<FArchive> FSerializeCtx::GetSiblingArchive(const char* Extension)
    {
        return Vfs.GetFile((PackageName + Extension).c_str());
    }
}