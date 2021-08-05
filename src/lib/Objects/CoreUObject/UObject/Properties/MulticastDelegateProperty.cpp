#pragma once

#include "BaseProperty.h"

namespace upp::Objects {
    MulticastDelegateProperty::BaseProperty(FArchive& Ar, const UPropertyTag& Tag, EReadType ReadType)
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