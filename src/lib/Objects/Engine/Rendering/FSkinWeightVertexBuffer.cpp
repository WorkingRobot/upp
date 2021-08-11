#include "FSkinWeightVertexBuffer.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FSkinWeightVertexBuffer& Value)
    {
        Ar >> Value.DataVertexBuffer;
        Ar >> Value.LookupVertexBuffer;

        return Ar;
    }
}