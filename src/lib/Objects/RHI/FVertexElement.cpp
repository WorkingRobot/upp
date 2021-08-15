#include "FVertexElement.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FVertexElement& Value)
    {
        Ar >> Value.StreamIndex;
        Ar >> Value.Offset;
        Ar >> Value.Type;
        Ar >> Value.AttributeIndex;
        Ar >> Value.Stride;
        Ar >> Value.bUseInstanceIndex;

        return Ar;
    }
}