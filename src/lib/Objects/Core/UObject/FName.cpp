#include "FName.h"

namespace upp::Objects {
    FName::FName(uint32_t Index, uint32_t Number) :
        Index(Index),
        Number(Number)
    {

    }

    FArchive& operator>>(FArchive& Ar, FName& Value)
    {
        Ar >> Value.Index;
        Ar >> Value.Number;

        return Ar;
    }
}