#pragma once

#include "BaseProperty.h"

namespace upp::Objects {
    ObjectProperty::BaseProperty(FArchive& Ar, const FPropertyTag& Tag, EReadType ReadType) :
        Value()
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