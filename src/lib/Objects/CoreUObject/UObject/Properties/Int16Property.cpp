#pragma once

#include "BaseProperty.h"

namespace upp::Objects {
    Int16Property::BaseProperty(FArchive& Ar, const FPropertyTag& Tag, EReadType ReadType) :
        Value(0)
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