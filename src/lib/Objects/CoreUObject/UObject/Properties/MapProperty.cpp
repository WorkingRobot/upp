#pragma once

#include "../UPropertyData.h"
#include "BaseProperty.h"

namespace upp::Objects {
    MapProperty::BaseProperty(FArchive& Ar, FSerializeCtx& Ctx, const UPropertyTag& Tag, EReadType ReadType)
    {
        switch (ReadType)
        {
        case EReadType::Normal:
        case EReadType::Array:
        case EReadType::Map:
            int NumKeysToRemove;
            Ar >> NumKeysToRemove;
            for (int i = 0; i < NumKeysToRemove; ++i) {
                UPropertyData(Ar, Ctx, *Tag.TagData.GetData().Map.InnerType, EReadType::Map);
            }

            int NumEntries;
            Ar >> NumEntries;
            Value.reserve(NumEntries);
            for (int i = 0; i < NumEntries; ++i) {
                Value.emplace_back(std::piecewise_construct, std::forward_as_tuple(Ar, Ctx, *Tag.TagData.GetData().Map.InnerType, EReadType::Map), std::forward_as_tuple(Ar, Ctx, *Tag.TagData.GetData().Map.ValueType, EReadType::Map));
            }
            break;
        }
    }
}