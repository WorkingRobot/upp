#include "FTexture2DMipMap.h"

namespace upp::Objects {
    void FTexture2DMipMap::Serialize(FArchive& Ar, FSerializeCtx& Ctx)
    {
        // Unused in production; used in the editor
        int IsCooked;
        Ar >> IsCooked;

        BulkData.Serialize(Ar, Ctx);

        Ar >> SizeX;
        Ar >> SizeY;
        Ar >> SizeZ;
    }
}