#include "FModelVertex.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FModelVertex& Value)
    {
        Ar >> Value.Position;
        Ar >> Value.TangentX;
        Ar >> Value.TangentZ;
        Ar >> Value.TexCoord;
        Ar >> Value.ShadowTexCoord;

        return Ar;
    }
}