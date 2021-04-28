#include "FPackageObjectIndex.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FPackageObjectIndex& Value)
    {
        Ar >> Value.TypeAndId;

        return Ar;
    }

    bool FPackageObjectIndex::IsValid() const
    {
        return TypeAndId != -1;
    }

    bool FPackageObjectIndex::IsExport() const
    {
        return GetType() == EPackageObjectIndexType::Export;
    }

    bool FPackageObjectIndex::IsImport() const
    {
        return IsScriptImport() || IsPackageImport();
    }

    bool FPackageObjectIndex::IsScriptImport() const
    {
        return GetType() == EPackageObjectIndexType::ScriptImport;
    }

    bool FPackageObjectIndex::IsPackageImport() const
    {
        return GetType() == EPackageObjectIndexType::PackageImport;
    }

    EPackageObjectIndexType FPackageObjectIndex::GetType() const
    {
        return (EPackageObjectIndexType)(TypeAndId >> 62);
    }

    uint64_t FPackageObjectIndex::GetValue() const
    {
        return TypeAndId & ((1ull << 62) - 1);
    }
}