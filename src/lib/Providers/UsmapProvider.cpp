#include "UsmapProvider.h"

#include "../Compression.h"
#include "../Objects/Core/Serialization/FByteArchive.h"
#include "Usmap/Header.h"

#include <unordered_map>

namespace upp::Providers {
    using namespace Usmap;
    using namespace Objects;

    template<class K, class V>
    struct MiniLUT {
        std::unordered_map<K, std::reference_wrapper<const V>> Data;

        void Add(K Key, const V& Value)
        {
            Data.emplace(Key, Value);
        }

        const V* Get(K Key) const
        {
            if (Key == -1) {
                return nullptr;
            }
            auto Itr = Data.find(Key);
            if (Itr != Data.end()) {
                return &Itr->second.get();
            }
            return nullptr;
        }
    };

    struct UsmapProvider::LUT {
        MiniLUT<uint32_t, Schema> Schemas;
        MiniLUT<uint32_t, Enum> Enums;
    };

    UsmapProvider::UsmapProvider(FArchive& Ar)
    {
        Header Header;
        Ar >> Header;
        if (Header.Magic == 0) {
            return;
        }

        std::unique_ptr<char[]> DecompData;
        {
            auto CompData = std::make_unique<char[]>(Header.CompSize);
            Ar.Read(CompData.get(), Header.CompSize);
            switch (Header.Method)
            {
            case ECompressionMethod::None:
                DecompData = std::move(CompData);
                break;
            case ECompressionMethod::Oodle:
                DecompData = std::make_unique<char[]>(Header.DecompSize);
                Compression::Decompress<CompressionMethod::Oodle>(CompData.get(), Header.CompSize, DecompData.get(), Header.DecompSize);
                break;
            case ECompressionMethod::Brotli:
                DecompData = std::make_unique<char[]>(Header.DecompSize);
                Compression::Decompress<CompressionMethod::Brotli>(CompData.get(), Header.CompSize, DecompData.get(), Header.DecompSize);
                break;
            default:
                return;
            }
        }

        FByteArchive DecompAr(std::move(DecompData), Header.DecompSize, Ar.GetName() + " Usmap Data");
        Serialize(DecompAr);
    }

    void UsmapProvider::Serialize(Objects::FArchive& Ar)
    {
        // Names
        {
            uint32_t NameCount;
            Ar >> NameCount;
            Names.reserve(NameCount);
            for (uint32_t Idx = 0; Idx < NameCount; ++Idx) {
                uint8_t NameSize;
                Ar >> NameSize;
                auto NameData = std::make_unique<char[]>(NameSize + 1);
                Ar.Read(NameData.get(), NameSize);
                NameData[NameSize] = '\0';
                Names.emplace_back(std::move(NameData));
            }
        }

        LUT LUT;

        // Enums
        {
            uint32_t EnumCount;
            Ar >> EnumCount;
            Enums.reserve(EnumCount);
            for (uint32_t Idx = 0; Idx < EnumCount; ++Idx) {
                uint32_t EnumNameIdx;
                Ar >> EnumNameIdx;

                std::vector<std::reference_wrapper<Name>> EnumNames;
                uint8_t NameCount;
                Ar >> NameCount;
                EnumNames.reserve(NameCount);
                for (uint8_t Idx = 0; Idx < NameCount; ++Idx) {
                    uint32_t NameIdx;
                    Ar >> NameIdx;
                    EnumNames.emplace_back(Names[NameIdx]);
                }

                auto& Enum = Enums.emplace_back<false>(Names[EnumNameIdx], Providers::Enum(Names[EnumNameIdx], std::move(EnumNames)));
                LUT.Enums.Add(EnumNameIdx, Enum);
            }
        }

        // Schemas
        {
            uint32_t SchemaCount;
            Ar >> SchemaCount;
            Schemas.reserve(SchemaCount);
            for (uint32_t Idx = 0; Idx < SchemaCount; ++Idx) {
                uint32_t SchemaNameIdx;
                uint32_t SchemaSuperNameIdx;
                uint16_t PropCount;
                uint16_t SerializablePropCount;
                Ar >> SchemaNameIdx;
                Ar >> SchemaSuperNameIdx;
                Ar >> PropCount;
                Ar >> SerializablePropCount;

                std::vector<Property> Props;
                Props.reserve(SerializablePropCount);
                for (uint16_t Idx = 0; Idx < SerializablePropCount; ++Idx) {
                    uint16_t SchemaIdx;
                    uint8_t ArraySize;
                    uint32_t NameIdx;
                    Ar >> SchemaIdx;
                    Ar >> ArraySize;
                    Ar >> NameIdx;
                    auto& Prop = Props.emplace_back(Names[NameIdx], SchemaIdx, ArraySize);
                    SerializePropData(Ar, Prop.Data, LUT);
                }

                auto& Schema = Schemas.emplace_back<false>(Names[SchemaNameIdx], Providers::Schema(Names[SchemaNameIdx], LUT.Schemas.Get(SchemaSuperNameIdx), PropCount, std::move(Props)));
                LUT.Schemas.Add(SchemaNameIdx, Schema);
            }
        }
    }

    void UsmapProvider::SerializePropData(Objects::FArchive& Ar, PropertyData& PropData, const LUT& LUT)
    {
        EPropertyType PropType;
        Ar >> PropType;
        auto& Data = PropData.GetData(PropType);
        switch (PropType)
        {
        case EPropertyType::EnumProperty:
        {
            Data.Enum.InnerType = std::make_unique<PropertyData>();

            SerializePropData(Ar, *Data.Enum.InnerType, LUT);
            uint32_t Idx;
            Ar >> Idx;
            Data.Enum.Enum = LUT.Enums.Get(Idx);
            break;
        }
        case EPropertyType::StructProperty:
        {
            uint32_t Idx;
            Ar >> Idx;
            Data.Struct.StructType = Names[Idx];
            Data.Struct.StructSchema = LUT.Schemas.Get(Idx);
            break;
        }
        case EPropertyType::SetProperty:
        case EPropertyType::ArrayProperty:
            Data.Array.InnerType = std::make_unique<PropertyData>();

            SerializePropData(Ar, *Data.Array.InnerType, LUT);
            break;
        case EPropertyType::MapProperty:
            Data.Map.InnerType = std::make_unique<PropertyData>();
            Data.Map.ValueType = std::make_unique<PropertyData>();

            SerializePropData(Ar, *Data.Map.InnerType, LUT);
            SerializePropData(Ar, *Data.Map.ValueType, LUT);
            break;
        default:
            break;
        }
    }
}