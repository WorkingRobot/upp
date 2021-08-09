#include "FSerializeCtx.h"

#include "../../../Vfs/Vfs.h"

namespace upp::Objects {
    FSerializeCtx::FSerializeCtx(Vfs::Vfs& Vfs, const FPackageId& PackageId, const std::vector<FPackageObjectIndex>& ImportMap, const std::vector<FExportMapEntry>& ExportMap) :
        Vfs(Vfs),
        PackageId(PackageId),
        ImportMap(ImportMap),
        ExportMap(ExportMap)
    {

    }

    Vfs::Vfs& FSerializeCtx::GetVfs()
    {
        return Vfs;
    }

    std::unique_ptr<FArchive> FSerializeCtx::GetSiblingArchive(EIoChunkType Type)
    {
        Vfs::File File;
        if (Vfs.FindChunk(FIoChunkId(PackageId.Id, 0, Type), File)) {
            return Vfs.GetFile(File);
        }
        return nullptr;
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