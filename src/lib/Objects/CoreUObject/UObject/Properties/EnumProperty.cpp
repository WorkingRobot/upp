#pragma once

#include "../../../../Providers/Enum.h"
#include "../FPropertyData.h"
#include "BaseProperty.h"

namespace upp::Objects {
    std::string GetEnumString(const Providers::Enum& Enum, size_t Idx)
    {
        return (std::string)Enum.Name + "::" + (Enum.Names.size() > Idx ? (std::string)Enum.Names[Idx].get() : std::to_string(Idx));
    }

    EnumProperty::BaseProperty(FArchive& Ar, const FPropertyTag& Tag, EReadType ReadType)
    {
        switch (ReadType)
        {
        case EReadType::Normal:
        {
            size_t EnumIdx;
            auto& InnerType = Tag.TagData.GetData().Enum.InnerType;
            if (InnerType) {
                FPropertyData Data(Ar, *InnerType, EReadType::Normal);

                std::visit([&EnumIdx](auto&& Data) {
                    using T = std::decay_t<decltype(Data)>;
                    if constexpr (std::is_same_v<T, std::monostate>) {
                        EnumIdx = -1;
                    }
                    else {
                        using DataT = std::decay_t<decltype(Data.Get())>;
                        if constexpr (std::is_integral_v<DataT>) {
                            EnumIdx = Data.Get();
                        }
                        else {
                            EnumIdx = -1;
                        }
                    }
                }, Data.Data);
            }
            else {
                uint8_t Idx;
                Ar >> Idx;
                EnumIdx = Idx;
            }
            Value = GetEnumString(*Tag.TagData.GetData().Enum.Enum, EnumIdx);
            break;
        }
        case EReadType::Array:
        case EReadType::Map:
            FName Name;
            Ar >> Name;
            Value = std::format("FName({}, {})", Name.Index, Name.Number);
            break;
        }
    }
};