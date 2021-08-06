#include "FVert.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FVert& Value)
    {
        Ar >> Value.pVertex;
		Ar >> Value.iSide;
		Ar >> Value.ShadowTexCoord;
		Ar >> Value.BackfaceShadowTexCoord;

        return Ar;
    }
}