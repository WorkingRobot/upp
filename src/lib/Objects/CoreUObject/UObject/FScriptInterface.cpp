#include "FScriptInterface.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FScriptInterface& Value)
    {
        Ar >> Value.ObjectRef;

        return Ar;
    }
}