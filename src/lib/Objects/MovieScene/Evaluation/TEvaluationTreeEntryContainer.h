#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "FEntry.h"

namespace upp::Objects {
    template<class T>
    struct TEvaluationTreeEntryContainer {
        std::vector<FEntry> Entries;
        std::vector<T> Items;

        friend FArchive& operator>>(FArchive& Ar, TEvaluationTreeEntryContainer& Value)
        {
            Ar >> Value.Entries;
            Ar >> Value.Items;

            return Ar;
        }
    };
}