#pragma once

#include "BaseProperty.h"

namespace upp::Objects {
    BoolProperty::BaseProperty(FArchive& Ar, const UPropertyTag& Tag, EReadType ReadType) :
        Value(false)
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