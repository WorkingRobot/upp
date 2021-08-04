#include "FSerializeCtx.h"

#include "../../../Vfs/Vfs.h"

namespace upp::Objects {
    FSerializeCtx::FSerializeCtx(Vfs::Vfs& Vfs, const std::string& PackageName, const std::vector<FPackageObjectIndex>& ImportMap, const std::vector<FExportMapEntry>& ExportMap) :
        Vfs(Vfs),
        PackageName(PackageName),
        ImportMap(ImportMap),
        ExportMap(ExportMap)
    {

    }

    Vfs::Vfs& FSerializeCtx::GetVfs()
    {
        return Vfs;
    }

    std::unique_ptr<FArchive> FSerializeCtx::GetSiblingArchive(const char* Extension)
    {
        return Vfs.GetFile((PackageName + "." + Extension).c_str());
    }

    const FPackageObjectIndex& FSerializeCtx::GetImport(uint32_t Idx) const
    {
        return ImportMap[Idx];
    }

    const FExportMapEntry& FSerializeCtx::GetExport(uint32_t Idx) const
    {
        return ExportMap[Idx];
    }

    const std::string& FSerializeCtx::GetObjectName(const FPackageObjectIndex& Idx) const
    {
        return Vfs.GetGlobalData().GetName(Vfs.GetGlobalData().GetEntry(Idx).ObjectName);
    }
}