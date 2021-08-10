#include "FFieldPath.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FFieldPath& Value)
    {
        Ar >> Value.Path;
        if (Value.Path.size() == 1 && Value.Path.front().IsNone()) {
            Value.Path.clear();
        }

        Ar >> Value.ResolvedOwner;

        return Ar;
    }
}