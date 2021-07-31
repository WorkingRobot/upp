#include "FScriptDelegate.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FScriptDelegate& Value)
    {
        Ar >> Value.Object;
        Ar >> Value.FunctionName;

        return Ar;
    }
}