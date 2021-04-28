#pragma once

#include "EPropertyType.h"
#include "Name.h"

namespace upp::Providers {
    class PropertyData {
        union DataUnion {
            struct EnumData {
                std::unique_ptr<PropertyData> InnerType;
                std::reference_wrapper<Name> EnumName;
            } Enum;
            struct StructData {
                std::reference_wrapper<Name> StructType;
            } Struct;
            struct ArrayData {
                std::unique_ptr<PropertyData> InnerType;
            } Array;
            struct MapData {
                std::unique_ptr<PropertyData> InnerType;
                std::unique_ptr<PropertyData> ValueType;
            } Map;

            DataUnion() {}
            ~DataUnion() {}
        } Data;

        EPropertyType Type;

        void ConstructUnion() {
            memset(&Data, 0, sizeof(Data));
        }

        void DestructUnion() {
            switch (Type)
            {
            case EPropertyType::EnumProperty:
                Data.Enum.~EnumData();
                break;
            case EPropertyType::StructProperty:
                Data.Struct.~StructData();
                break;
            case EPropertyType::SetProperty:
            case EPropertyType::ArrayProperty:
                Data.Array.~ArrayData();
                break;
            case EPropertyType::MapProperty:
                Data.Map.~MapData();
                break;
            }
        }

    public:
        PropertyData() :
            Type(EPropertyType::Unknown)
        {
            ConstructUnion();
        }

        PropertyData(PropertyData&& Other) noexcept :
            Type(Other.Type)
        {
            ConstructUnion();
            switch (Type)
            {
            case EPropertyType::EnumProperty:
                Data.Enum = std::move(Other.Data.Enum);
                break;
            case EPropertyType::StructProperty:
                Data.Struct = std::move(Other.Data.Struct);
                break;
            case EPropertyType::SetProperty:
            case EPropertyType::ArrayProperty:
                Data.Array = std::move(Other.Data.Array);
                break;
            case EPropertyType::MapProperty:
                Data.Map = std::move(Other.Data.Map);
                break;
            }
        }

        ~PropertyData() {
            DestructUnion();
        }

        EPropertyType GetType() const {
            return Type;
        }

        const DataUnion& GetData() const {
            return Data;
        }

        DataUnion& GetData(EPropertyType RequestedType) {
            if (Type != RequestedType) {
                DestructUnion();
                Type = RequestedType;
                ConstructUnion();
            }
            return Data;
        }
    };
}