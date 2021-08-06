#include "FCompressedVisibilityChunk.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FCompressedVisibilityChunk& Value)
    {
        int bCompressed;
        Ar >> bCompressed;
        Value.IsCompressed = bCompressed;
        Ar >> Value.UncompressedSize;
        Ar >> Value.Data;

        return Ar;
    }
}