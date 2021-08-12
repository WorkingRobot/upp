#pragma once

#include "../../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FEvaluationTreeEntryHandle {
        int EntryIndex;

        friend FArchive& operator>>(FArchive& Ar, FEvaluationTreeEntryHandle& Value);
    };
}