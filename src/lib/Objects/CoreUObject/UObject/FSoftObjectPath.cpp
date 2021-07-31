#include "FSoftObjectPath.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FSoftObjectPath& Value)
    {
        Ar >> Value.AssetPathName;
        Ar >> Value.SubPathString;

        return Ar;
    }
}