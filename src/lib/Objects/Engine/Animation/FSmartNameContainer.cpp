#include "FSmartNameContainer.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FSmartNameContainer& Value)
    {
        Ar >> Value.NameMappings;

        return Ar;
    }
}