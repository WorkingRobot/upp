#include "FText.h"

#include "ETextHistoryType.h"
#include "FTextHistory.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FText& Value)
    {
        Ar >> Value.Flags;
        // "Assuming" the reader/archive is persistent
        Value.Flags = ETextFlag((uint32_t)Value.Flags & ((uint32_t)ETextFlag::ConvertedProperty | (uint32_t)ETextFlag::InitializedFromString));

        Value.History = std::make_shared<FTextHistory>();
        Ar >> *Value.History;

        return Ar;
    }
}