#pragma once

#include "BaseProperty.h"

namespace upp::Objects {
    LazyObjectProperty::BaseProperty(FArchive& Ar, const FPropertyTag& Tag, EReadType ReadType)
    {
        switch (ReadType)
        {
        case EReadType::Normal:
        case EReadType::Array:
        case EReadType::Map:
            Ar >> Value;
            break;
        }
    }
}