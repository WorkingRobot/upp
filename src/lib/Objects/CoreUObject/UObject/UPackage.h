#pragma once

#include "UObject.h"

#include <vector>

namespace upp::Objects {
    struct UPackage {
        std::vector<std::unique_ptr<UObject>> Exports;

        std::vector<std::string> NameMap;
        std::vector<FPackageObjectIndex> ImportMap;
        std::vector<FExportMapEntry> ExportMap;
    };
}