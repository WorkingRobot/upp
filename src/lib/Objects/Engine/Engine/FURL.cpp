#include "FURL.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FURL& Value)
    {
        Ar >> Value.Protocol;
        Ar >> Value.Host;
        Ar >> Value.Map;
        Ar >> Value.Portal;
        Ar >> Value.Op;
        Ar >> Value.Port;
        Ar >> Value.Valid;

        return Ar;
    }
}