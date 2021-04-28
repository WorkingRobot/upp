#include "FMappedName.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FMappedName& Value)
    {
        Ar >> Value.Index;
        Ar >> Value.Number;

        return Ar;
    }

    bool FMappedName::IsValid() const
    {
        return Index != -1 && Number != -1;
    }

    EMappedNameType FMappedName::GetType() const
    {
        return (EMappedNameType)(Index >> 30);
    }

    bool FMappedName::IsGlobal() const
    {
        return GetType() != EMappedNameType::Package;
    }

    uint32_t FMappedName::GetIndex() const
    {
        return Index & ((1ull << 30) - 1);
    }

    uint32_t FMappedName::GetNumber() const
    {
        return Number;
    }
}