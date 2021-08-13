#include "FShaderMapEntry.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FShaderMapEntry& Value)
    {
        Ar >> Value.ShaderIndicesOffset;
        Ar >> Value.NumShaders;
        Ar >> Value.FirstPreloadIndex;
        Ar >> Value.NumPreloadEntries;

        return Ar;
    }
}