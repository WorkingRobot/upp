#include "FPipelineCacheFileFormatHeader.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FPipelineCacheFileFormatHeader& Value)
    {
        Ar >> Value.Magic;
        Ar >> Value.Version;
        Ar >> Value.GameVersion;
        Ar >> Value.Platform;
        Ar >> Value.Guid;
        Ar >> Value.TableOffset;

        return Ar;
    }
}