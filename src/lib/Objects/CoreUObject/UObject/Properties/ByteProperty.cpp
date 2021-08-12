#pragma once

#include "BaseProperty.h"

namespace upp::Objects {
    ByteProperty::BaseProperty(FArchive& Ar, FSerializeCtx& Ctx, const UPropertyTag& Tag, EReadType ReadType) :
        Value(0)
    {
        switch (ReadType)
        {
        case EReadType::Normal:
        case EReadType::Array:
            Ar >> Value;
            break;
        case EReadType::Map:
            uint32_t Data;
            Ar >> Data;
            Value = Data;
            break;
        }
    }
}