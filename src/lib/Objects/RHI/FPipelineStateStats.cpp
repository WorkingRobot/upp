#include "FPipelineStateStats.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FPipelineStateStats& Value)
    {
        Ar >> Value.FirstFrameUsed;
        Ar >> Value.LastFrameUsed;
        Ar >> Value.CreateCount;
        Ar >> Value.TotalBindCount;
        Ar >> Value.PSOHash;

        return Ar;
    }
}