#pragma once

#include "UPropertyData.h"

namespace upp::Objects {
    struct UProperty {
        UProperty(FArchive& Ar, const Providers::Property& PropertyInfo, EReadType ReadType);

        ~UProperty();

        UPropertyTag Tag;

        UPropertyData Data;

        template<class T>
        const T* Get() const
        {
            return std::visit([](const auto& Data) -> const T* {
                using DataT = std::decay_t<decltype(*Data)>;
                if constexpr (std::is_same_v<DataT, T>) {
                    return &*Data;
                }
                if constexpr (std::is_same_v<DataT, std::any>) {
                    return std::any_cast<T>(&*Data);
                }
                return nullptr;
            }, Data.Data);
        }
    };
}