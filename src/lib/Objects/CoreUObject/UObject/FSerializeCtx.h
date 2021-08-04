#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "../Serialization/FExportMapEntry.h"

namespace upp::Vfs {
    class Vfs;
}

namespace upp::Objects {
    struct FSerializeCtx {
    public:
        FSerializeCtx(Vfs::Vfs& Vfs, const std::string& PackageName, const std::vector<FPackageObjectIndex>& ImportMap, const std::vector<FExportMapEntry>& ExportMap);

        Vfs::Vfs& GetVfs();

        std::unique_ptr<FArchive> GetSiblingArchive(const char* Extension);

        const FPackageObjectIndex& GetImport(uint32_t Idx) const;

        const FExportMapEntry& GetExport(uint32_t Idx) const;

        const std::string& GetObjectName(const FPackageObjectIndex& Idx) const;

    private:
        Vfs::Vfs& Vfs;
        const std::string PackageName;
        const std::vector<FPackageObjectIndex>& ImportMap;
        const std::vector<FExportMapEntry>& ExportMap;
    };
}