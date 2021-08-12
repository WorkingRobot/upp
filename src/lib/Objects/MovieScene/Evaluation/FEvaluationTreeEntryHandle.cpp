#include "FEvaluationTreeEntryHandle.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FEvaluationTreeEntryHandle& Value)
    {
        Ar >> Value.EntryIndex;

        return Ar;
    }
}