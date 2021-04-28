#include "Header.h"

namespace upp::Providers::Usmap {
    using namespace Objects;

    FArchive& operator>>(FArchive& Ar, Header& Value)
    {
        Ar >> Value.Magic;
        if (Value.Magic != Header::FileMagic) {
            Value.Magic = 0;
            return Ar;
        }

        Ar >> Value.Version;
        Ar >> Value.Method;
        Ar >> Value.CompSize;
        Ar >> Value.DecompSize;

        return Ar;
    }
}