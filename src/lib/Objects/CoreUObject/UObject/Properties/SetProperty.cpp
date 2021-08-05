#pragma once

#include "../UPropertyData.h"
#include "BaseProperty.h"

namespace upp::Objects {
    SetProperty::BaseProperty(FArchive& Ar, const UPropertyTag& Tag, EReadType ReadType)
    {
        switch (ReadType)
        {
        case EReadType::Normal:
        case EReadType::Array:
        case EReadType::Map:
            int NumKeysToRemove;
            Ar >> NumKeysToRemove;
            for (int i = 0; i < NumKeysToRemove; ++i) {
                UPropertyData(Ar, *Tag.TagData.GetData().Array.InnerType, EReadType::Array);
            }

            int NumEntries;
            Ar >> NumEntries;
            Value.reserve(NumEntries);
            for (int i = 0; i < NumEntries; ++i) {
                Value.emplace_back(Ar, *Tag.TagData.GetData().Array.InnerType, EReadType::Array);
            }
            break;
        }
    }
}