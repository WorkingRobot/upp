#include "FReferencePose.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FReferencePose& Value)
    {
        Ar >> Value.PoseName;
        Ar >> Value.ReferencePose;

        return Ar;
    }
}