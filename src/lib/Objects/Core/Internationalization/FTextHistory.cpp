#include "FTextHistory.h"


namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FTextHistory& Value)
    {
        ETextHistoryType Type;
        Ar >> Type;

        switch (Type)
        {
        case ETextHistoryType::None:
            Ar >> Value.Data.emplace<FTextHistoryData<ETextHistoryType::None>>();
            break;
        case ETextHistoryType::Base:
            Ar >> Value.Data.emplace<FTextHistoryData<ETextHistoryType::Base>>();
            break;
        case ETextHistoryType::NamedFormat:
            Ar >> Value.Data.emplace<FTextHistoryData<ETextHistoryType::NamedFormat>>();
            break;
        case ETextHistoryType::OrderedFormat:
            Ar >> Value.Data.emplace<FTextHistoryData<ETextHistoryType::OrderedFormat>>();
            break;
        case ETextHistoryType::ArgumentFormat:
            Ar >> Value.Data.emplace<FTextHistoryData<ETextHistoryType::ArgumentFormat>>();
            break;
        case ETextHistoryType::AsNumber:
            Ar >> Value.Data.emplace<FTextHistoryData<ETextHistoryType::AsNumber>>();
            break;
        case ETextHistoryType::AsPercent:
            Ar >> Value.Data.emplace<FTextHistoryData<ETextHistoryType::AsPercent>>();
            break;
        case ETextHistoryType::AsCurrency:
            Ar >> Value.Data.emplace<FTextHistoryData<ETextHistoryType::AsCurrency>>();
            break;
        case ETextHistoryType::AsDate:
            Ar >> Value.Data.emplace<FTextHistoryData<ETextHistoryType::AsDate>>();
            break;
        case ETextHistoryType::AsTime:
            Ar >> Value.Data.emplace<FTextHistoryData<ETextHistoryType::AsTime>>();
            break;
        case ETextHistoryType::AsDateTime:
            Ar >> Value.Data.emplace<FTextHistoryData<ETextHistoryType::AsDateTime>>();
            break;
        case ETextHistoryType::Transform:
            Ar >> Value.Data.emplace<FTextHistoryData<ETextHistoryType::Transform>>();
            break;
        case ETextHistoryType::StringTableEntry:
            Ar >> Value.Data.emplace<FTextHistoryData<ETextHistoryType::StringTableEntry>>();
            break;
        case ETextHistoryType::TextGenerator:
            Ar >> Value.Data.emplace<FTextHistoryData<ETextHistoryType::TextGenerator>>();
            break;
        }

        return Ar;
    }
}