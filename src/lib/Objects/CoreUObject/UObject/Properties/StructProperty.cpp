#pragma once

#include "../../../../Crc32.h"
#include "../../../../Providers/Schema.h"
#include "../../../Core/Math/FLinearColor.h"
#include "../../../Core/Misc/FGuid.h"
#include "../UObject.h"
#include "BaseProperty.h"

namespace upp::Objects {
    StructProperty::BaseProperty(FArchive& Ar, const FPropertyTag& Tag, EReadType ReadType)
    {
        auto& StructType = Tag.TagData.GetData().Struct.StructType.get();
        switch (Crc32(StructType.GetString(), StructType.GetSize()))
        {
#define CASE(Name, Type) case Crc32(Name): { auto& Data = Value.emplace<Type>(); if (ReadType != EReadType::Zero) { Ar >> Data; } break; }

            CASE("Guid", FGuid);
            CASE("LinearColor", FLinearColor);

#undef CASE
        default:
            if (ReadType != EReadType::Zero) {
                Value.emplace<UObject>(UObject(Ar, *Tag.TagData.GetData().Struct.StructSchema));
            }
            else {
                Value.emplace<std::monostate>();
            }
            break;
        }
    }
}