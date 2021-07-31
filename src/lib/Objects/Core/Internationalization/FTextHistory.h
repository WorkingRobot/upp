#pragma once

#include "../Serialization/FArchive.h"
#include "FTextHistoryData.h"

namespace upp::Objects {
    struct FTextHistory {
        std::variant<
            FTextHistoryData<ETextHistoryType::None>,
            FTextHistoryData<ETextHistoryType::Base>,
            FTextHistoryData<ETextHistoryType::NamedFormat>,
            FTextHistoryData<ETextHistoryType::OrderedFormat>,
            FTextHistoryData<ETextHistoryType::ArgumentFormat>,
            FTextHistoryData<ETextHistoryType::AsNumber>,
            FTextHistoryData<ETextHistoryType::AsPercent>,
            FTextHistoryData<ETextHistoryType::AsCurrency>,
            FTextHistoryData<ETextHistoryType::AsDate>,
            FTextHistoryData<ETextHistoryType::AsTime>,
            FTextHistoryData<ETextHistoryType::AsDateTime>,
            FTextHistoryData<ETextHistoryType::Transform>,
            FTextHistoryData<ETextHistoryType::StringTableEntry>,
            FTextHistoryData<ETextHistoryType::TextGenerator>
        > Data;

        friend FArchive& operator>>(FArchive& Ar, FTextHistory& Value);
    };
}