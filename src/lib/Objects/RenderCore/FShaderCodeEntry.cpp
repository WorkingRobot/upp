#include "FShaderCodeEntry.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FShaderCodeEntry& Value)
    {
        Ar >> Value.Offset;
        Ar >> Value.Size;
        Ar >> Value.UncompressedSize;
        Ar >> Value.Frequency;

        return Ar;
    }
}