#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "../../Core/UObject/FName.h"

namespace upp::Objects {
    struct FSoftObjectPath {
        FName AssetPathName;
        std::string SubPathString;

        friend FArchive& operator>>(FArchive& Ar, FSoftObjectPath& Value);
    };
}