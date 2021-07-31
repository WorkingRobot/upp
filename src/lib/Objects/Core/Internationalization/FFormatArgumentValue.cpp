#include "FFormatArgumentValue.h"

#include "EFormatArgumentType.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FFormatArgumentValue& Value)
    {
        EFormatArgumentType Type;
        Ar >> Type;
        switch (Type)
        {
        case EFormatArgumentType::Int:
            Ar >> Value.Value.emplace<int64_t>();
            break;
        case EFormatArgumentType::UInt:
            Ar >> Value.Value.emplace<uint64_t>();
            break;
        case EFormatArgumentType::Float:
            Ar >> Value.Value.emplace<float>();
            break;
        case EFormatArgumentType::Double:
            Ar >> Value.Value.emplace<double>();
            break;
        case EFormatArgumentType::Text:
            Ar >> Value.Value.emplace<FText>();
            break;
        }

        return Ar;
    }
}