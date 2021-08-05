#pragma once

#include "../../../Core/Internationalization/FText.h"
#include "../../../Core/UObject/FName.h"
#include "../FFieldPath.h"
#include "../FPackageIndex.h"
#include "../UPropertyTag.h"
#include "../FMulticastScriptDelegate.h"
#include "../FScriptDelegate.h"
#include "../FScriptInterface.h"
#include "../FSoftObjectPath.h"
#include "../FUniqueObjectGuid.h"

#include <any>

namespace upp::Objects {
    enum class EReadType : uint8_t
    {
        Normal,
        Array,
        Map,
        Zero
    };

    struct UPropertyData;

    namespace Detail {
        using namespace Providers;

        template<EPropertyType Type>
        struct PropertyTraits;

#define CASE(Enum, ...) template<> struct PropertyTraits<Enum> { using T = __VA_ARGS__; }

        CASE(EPropertyType::ByteProperty, uint8_t);
        CASE(EPropertyType::BoolProperty, bool);
        CASE(EPropertyType::IntProperty, int32_t);
        CASE(EPropertyType::FloatProperty, float);
        CASE(EPropertyType::ObjectProperty, FPackageIndex);
        CASE(EPropertyType::NameProperty, FName);
        CASE(EPropertyType::DelegateProperty, FScriptDelegate);
        CASE(EPropertyType::DoubleProperty, double);
        CASE(EPropertyType::ArrayProperty, std::vector<UPropertyData>);
        CASE(EPropertyType::StructProperty, std::any);
        CASE(EPropertyType::StrProperty, std::string);
        CASE(EPropertyType::TextProperty, FText);
        CASE(EPropertyType::InterfaceProperty, FScriptInterface);
        CASE(EPropertyType::MulticastDelegateProperty, FMulticastScriptDelegate);
        CASE(EPropertyType::WeakObjectProperty, FPackageIndex);
        CASE(EPropertyType::LazyObjectProperty, FUniqueObjectGuid);
        CASE(EPropertyType::AssetObjectProperty, FSoftObjectPath);
        CASE(EPropertyType::SoftObjectProperty, FSoftObjectPath);
        CASE(EPropertyType::UInt64Property, uint64_t);
        CASE(EPropertyType::UInt32Property, uint32_t);
        CASE(EPropertyType::UInt16Property, uint16_t);
        CASE(EPropertyType::Int64Property, int64_t);
        CASE(EPropertyType::Int16Property, int16_t);
        CASE(EPropertyType::Int8Property, int8_t);
        CASE(EPropertyType::MapProperty, std::vector<std::pair<UPropertyData, UPropertyData>>);
        CASE(EPropertyType::SetProperty, std::vector<UPropertyData>);
        CASE(EPropertyType::EnumProperty, std::string);
        CASE(EPropertyType::FieldPathProperty, FFieldPath);

#undef CASE
    }
    

    template<Providers::EPropertyType Type, class T = Detail::PropertyTraits<Type>::T>
    struct BaseProperty {
        const T& Get() const
        {
            return Value;
        }

        const T& operator*() const
        {
            return Value;
        }

        const T* operator->() const
        {
            return &Value;
        }

        BaseProperty(FArchive& Ar, const UPropertyTag& Tag, EReadType ReadType);

    protected:
        BaseProperty() = default;

        T Value;
    };

    using ByteProperty = BaseProperty<Providers::EPropertyType::ByteProperty>;
    using BoolProperty = BaseProperty<Providers::EPropertyType::BoolProperty>;
    using IntProperty = BaseProperty<Providers::EPropertyType::IntProperty>;
    using FloatProperty = BaseProperty<Providers::EPropertyType::FloatProperty>;
    using ObjectProperty = BaseProperty<Providers::EPropertyType::ObjectProperty>;
    using NameProperty = BaseProperty<Providers::EPropertyType::NameProperty>;
    using DelegateProperty = BaseProperty<Providers::EPropertyType::DelegateProperty>;
    using DoubleProperty = BaseProperty<Providers::EPropertyType::DoubleProperty>;
    using ArrayProperty = BaseProperty<Providers::EPropertyType::ArrayProperty>;
    using StructProperty = BaseProperty<Providers::EPropertyType::StructProperty>;
    using StrProperty = BaseProperty<Providers::EPropertyType::StrProperty>;
    using TextProperty = BaseProperty<Providers::EPropertyType::TextProperty>;
    using InterfaceProperty = BaseProperty<Providers::EPropertyType::InterfaceProperty>;
    using MulticastDelegateProperty = BaseProperty<Providers::EPropertyType::MulticastDelegateProperty>;
    using WeakObjectProperty = BaseProperty<Providers::EPropertyType::WeakObjectProperty>;
    using LazyObjectProperty = BaseProperty<Providers::EPropertyType::LazyObjectProperty>;
    using AssetObjectProperty = BaseProperty<Providers::EPropertyType::AssetObjectProperty>;
    using SoftObjectProperty = BaseProperty<Providers::EPropertyType::SoftObjectProperty>;
    using UInt64Property = BaseProperty<Providers::EPropertyType::UInt64Property>;
    using UInt32Property = BaseProperty<Providers::EPropertyType::UInt32Property>;
    using UInt16Property = BaseProperty<Providers::EPropertyType::UInt16Property>;
    using Int64Property = BaseProperty<Providers::EPropertyType::Int64Property>;
    using Int16Property = BaseProperty<Providers::EPropertyType::Int16Property>;
    using Int8Property = BaseProperty<Providers::EPropertyType::Int8Property>;
    using MapProperty = BaseProperty<Providers::EPropertyType::MapProperty>;
    using SetProperty = BaseProperty<Providers::EPropertyType::SetProperty>;
    using EnumProperty = BaseProperty<Providers::EPropertyType::EnumProperty>;
    using FieldPathProperty = BaseProperty<Providers::EPropertyType::FieldPathProperty>;
}