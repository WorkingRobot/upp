#pragma once

#include "BaseProperty.h"

namespace upp::Objects {
    FieldPathProperty::BaseProperty(FArchive& Ar, FSerializeCtx& Ctx, const UPropertyTag& Tag, EReadType ReadType)
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