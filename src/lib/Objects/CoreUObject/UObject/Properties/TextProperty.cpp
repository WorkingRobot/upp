#pragma once

#include "BaseProperty.h"

namespace upp::Objects {
    TextProperty::BaseProperty(FArchive& Ar, const UPropertyTag& Tag, EReadType ReadType) :
        Value{nullptr, ETextFlag::Immutable}
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