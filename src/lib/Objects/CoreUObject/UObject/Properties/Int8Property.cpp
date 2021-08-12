#pragma once

#include "BaseProperty.h"

namespace upp::Objects {
    Int8Property::BaseProperty(FArchive& Ar, FSerializeCtx& Ctx, const UPropertyTag& Tag, EReadType ReadType) :
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