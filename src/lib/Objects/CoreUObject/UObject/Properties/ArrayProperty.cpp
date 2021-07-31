#pragma once

#include "../FPropertyData.h"
#include "BaseProperty.h"

namespace upp::Objects {
    ArrayProperty::BaseProperty(FArchive& Ar, const FPropertyTag& Tag, EReadType ReadType)
    {
        switch (ReadType)
        {
        case EReadType::Normal:
        case EReadType::Array:
        case EReadType::Map:
            int SerializeNum;
            Ar >> SerializeNum;
            Value.reserve(SerializeNum);
            for (int i = 0; i < SerializeNum; ++i) {
                Value.emplace_back(Ar, *Tag.TagData.GetData().Array.InnerType, EReadType::Array);
            }
            break;
        }
    }
}