#pragma once

#include "../../../../Providers/Enum.h"
#include "../UPropertyData.h"
#include "BaseProperty.h"

namespace upp::Objects {
    EnumProperty::BaseProperty(FArchive& Ar, const UPropertyTag& Tag, EReadType ReadType)
    {
        switch (ReadType)
        {
        case EReadType::Normal:
        {
            size_t EnumIdx;
            auto& InnerType = Tag.TagData.GetData().Enum.InnerType;
            if (InnerType) {
                UPropertyData Data(Ar, *InnerType, EReadType::Normal);

                std::visit([&EnumIdx](auto&& Data) {
                    using T = std::decay_t<decltype(Data)>;
                    using DataT = std::decay_t<decltype(Data.Get())>;
                    if constexpr (std::is_integral_v<DataT>) {
                        EnumIdx = Data.Get();
                    }
                    else {
                        EnumIdx = -1;
                    }
                }, Data.Data);
            }
            else {
                uint8_t Idx;
                Ar >> Idx;
                EnumIdx = Idx;
            }
            auto& Enum = *Tag.TagData.GetData().Enum.Enum;
            Value = Enum.Names.size() > EnumIdx ? (std::string)Enum.Names[EnumIdx].get() : std::to_string(EnumIdx);
            break;
        }
        case EReadType::Array:
        case EReadType::Map:
        {
            FName Name;
            Ar >> Name;
            Value = Name;
            break;
        }
        }
    }
};