#include "UObject.h"

namespace upp::Objects {
    std::unique_ptr<UObject> UObject::SerializeUnversioned(FArchive& Ar, const std::string& ClassName, Vfs::Vfs& Vfs)
    {
        return nullptr;
    }
}