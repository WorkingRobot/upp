#include "FPackageIndex.h"

namespace upp::Objects {
    FPackageIndex::FPackageIndex(int32_t Idx) :
        Idx(Idx)
    {

    }

    FArchive& operator>>(FArchive& Ar, FPackageIndex& Value)
    {
        Ar >> Value.Idx;

        return Ar;
    }

    bool FPackageIndex::IsValid() const
    {
        return Idx != 0;
    }

    bool FPackageIndex::IsExport() const
    {
        return Idx > 0;
    }

    bool FPackageIndex::IsImport() const
    {
        return Idx < 0;
    }

    uint32_t FPackageIndex::GetValue() const
    {
        return !IsValid() ? 0 : IsImport() ? -Idx - 1 : Idx - 1;
    }
}