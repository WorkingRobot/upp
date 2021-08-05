#include "FPropertyData.h"

#include "../../../Crc32.h"
#include "FProperty.h"

namespace upp::Objects {
    void FPropertyData::ConstructUnion()
    {
        memset(&Data, 0, sizeof(Data));
    }

    void FPropertyData::DestructUnion()
    {
        switch (Type)
        {
#define CASE(Name) case EFPropertyType::F##Name##Property: Data.Name.~F##Name##Property(); break

            CASE(Array);
            CASE(Bool);
            CASE(Byte);
            CASE(Class);
            CASE(Delegate);
            CASE(Enum);
            CASE(FieldPath);
            CASE(Float);
            CASE(Int64);
            CASE(Int16);
            CASE(Int8);
            CASE(Int);
            CASE(Interface);
            CASE(Map);
            CASE(MulticastDelegate);
            CASE(MulticastInlineDelegate);
            CASE(Name);
            CASE(Object);
            CASE(Set);
            CASE(SoftClass);
            CASE(SoftObject);
            CASE(Str);
            CASE(Struct);
            CASE(Text);
            CASE(UInt16);
            CASE(UInt32);
            CASE(UInt64);

#undef CASE
        }
    }

    FPropertyData::FPropertyData() :
        Type(EFPropertyType::Unknown)
    {
        ConstructUnion();
    }

    FPropertyData::FPropertyData(const FPropertyData& Other) :
        Type(Other.Type)
    {
        ConstructUnion();
        switch (Type)
        {
        case EFPropertyType::FArrayProperty:
            Data.Array.Property = std::make_unique<FProperty>(*Other.Data.Array.Property);
            break;
        case EFPropertyType::FBoolProperty:
            Data.Bool.FieldSize = Other.Data.Bool.FieldSize;
            Data.Bool.ByteOffset = Other.Data.Bool.ByteOffset;
            Data.Bool.ByteMask = Other.Data.Bool.ByteMask;
            Data.Bool.FieldMask = Other.Data.Bool.FieldMask;
            Data.Bool.BoolSize = Other.Data.Bool.BoolSize;
            Data.Bool.bIsNativeBool = Other.Data.Bool.bIsNativeBool;
            break;
        case EFPropertyType::FByteProperty:
            Data.Byte.Enum = Other.Data.Byte.Enum;
            break;
        case EFPropertyType::FClassProperty:
            Data.Class.PropertyClass = Other.Data.Class.PropertyClass;
            Data.Class.MetaClass = Other.Data.Class.MetaClass;
            break;
        case EFPropertyType::FDelegateProperty:
            Data.Delegate.SignatureFunction = Other.Data.Delegate.SignatureFunction;
            break;
        case EFPropertyType::FEnumProperty:
            Data.Enum.UnderlyingProp = std::make_unique<FProperty>(*Other.Data.Enum.UnderlyingProp);
            Data.Enum.Enum = Other.Data.Enum.Enum;
            break;
        case EFPropertyType::FFieldPathProperty:
            Data.FieldPath.PropertyClass = Other.Data.FieldPath.PropertyClass;
            break;
        case EFPropertyType::FFloatProperty:
            break;
        case EFPropertyType::FInt16Property:
            break;
        case EFPropertyType::FInt64Property:
            break;
        case EFPropertyType::FInt8Property:
            break;
        case EFPropertyType::FIntProperty:
            break;
        case EFPropertyType::FInterfaceProperty:
            Data.Interface.InterfaceClass = Other.Data.Interface.InterfaceClass;
            break;
        case EFPropertyType::FMapProperty:
            Data.Map.KeyProp = std::make_unique<FProperty>(*Other.Data.Map.KeyProp);
            Data.Map.ValueProp = std::make_unique<FProperty>(*Other.Data.Map.ValueProp);
            break;
        case EFPropertyType::FMulticastDelegateProperty:
            Data.MulticastDelegate.SignatureFunction = Other.Data.MulticastDelegate.SignatureFunction;
            break;
        case EFPropertyType::FMulticastInlineDelegateProperty:
            Data.MulticastInlineDelegate.SignatureFunction = Other.Data.MulticastInlineDelegate.SignatureFunction;
            break;
        case EFPropertyType::FNameProperty:
            break;
        case EFPropertyType::FObjectProperty:
            Data.Object.PropertyClass = Other.Data.Object.PropertyClass;
            break;
        case EFPropertyType::FSetProperty:
            Data.Set.ElementProp = std::make_unique<FProperty>(*Other.Data.Set.ElementProp);
            break;
        case EFPropertyType::FSoftClassProperty:
            Data.SoftClass.PropertyClass = Other.Data.SoftClass.PropertyClass;
            Data.SoftClass.MetaClass = std::make_unique<FProperty>(*Other.Data.SoftClass.MetaClass);
            break;
        case EFPropertyType::FSoftObjectProperty:
            Data.SoftObject.PropertyClass = Other.Data.SoftObject.PropertyClass;
            break;
        case EFPropertyType::FStrProperty:
            break;
        case EFPropertyType::FStructProperty:
            Data.Struct.Struct = Other.Data.Struct.Struct;
            break;
        case EFPropertyType::FTextProperty:
            break;
        case EFPropertyType::FUInt16Property:
            break;
        case EFPropertyType::FUInt32Property:
            break;
        case EFPropertyType::FUInt64Property:
            break;
        }
    }

    FPropertyData::FPropertyData(FPropertyData&& Other) noexcept :
        Type(Other.Type)
    {
        ConstructUnion();
        switch (Type)
        {
#define CASE(Name) case EFPropertyType::F##Name##Property: Data.Name = std::move(Other.Data.Name); break

            CASE(Array);
            CASE(Bool);
            CASE(Byte);
            CASE(Class);
            CASE(Delegate);
            CASE(Enum);
            CASE(FieldPath);
            CASE(Float);
            CASE(Int64);
            CASE(Int16);
            CASE(Int8);
            CASE(Int);
            CASE(Interface);
            CASE(Map);
            CASE(MulticastDelegate);
            CASE(MulticastInlineDelegate);
            CASE(Name);
            CASE(Object);
            CASE(Set);
            CASE(SoftClass);
            CASE(SoftObject);
            CASE(Str);
            CASE(Struct);
            CASE(Text);
            CASE(UInt16);
            CASE(UInt32);
            CASE(UInt64);

#undef CASE
        }
    }

    FPropertyData::FPropertyData(FArchive& Ar, const std::string& Type) :
        FPropertyData()
    {
        switch (Crc32(Type))
        {
#define STRINGIZE_(Val) #Val
#define STRINGIZE(Val) STRINGIZE_(Val)
#define CASE(Name) case Crc32(STRINGIZE(Name##Property)): Ar >> Data.Name; this->Type = EFPropertyType::F##Name##Property; break

            CASE(Array);
            CASE(Bool);
            CASE(Byte);
            CASE(Class);
            CASE(Delegate);
            CASE(Enum);
            CASE(FieldPath);
            CASE(Float);
            CASE(Int64);
            CASE(Int16);
            CASE(Int8);
            CASE(Int);
            CASE(Interface);
            CASE(Map);
            CASE(MulticastDelegate);
            CASE(MulticastInlineDelegate);
            CASE(Name);
            CASE(Object);
            CASE(Set);
            CASE(SoftClass);
            CASE(SoftObject);
            CASE(Str);
            CASE(Struct);
            CASE(Text);
            CASE(UInt16);
            CASE(UInt32);
            CASE(UInt64);

#undef CASE
        }
    }

    FPropertyData::~FPropertyData()
    {
        DestructUnion();
    }

    EFPropertyType FPropertyData::GetType() const
    {
        return Type;
    }

    const FPropertyData::DataUnion& FPropertyData::GetData() const
    {
        return Data;
    }

    FPropertyData::DataUnion& FPropertyData::GetData(EFPropertyType RequestedType)
    {
        if (Type != RequestedType) {
            DestructUnion();
            ConstructUnion();
            Type = RequestedType;
        }
        return Data;
    }

    using Data = std::decay_t<decltype(FPropertyData().GetData())>;

    FArchive& operator>>(FArchive& Ar, Data::FArrayProperty& Value)
    {
        Value.Property = FProperty::SerializeSingleField(Ar);

        return Ar;
    }

    FArchive& operator>>(FArchive& Ar, Data::FBoolProperty& Value)
    {
        Ar >> Value.FieldSize;
        Ar >> Value.ByteOffset;
        Ar >> Value.ByteMask;
        Ar >> Value.FieldMask;
        Ar >> Value.BoolSize;
        Ar >> Value.bIsNativeBool;

        return Ar;
    }

    FArchive& operator>>(FArchive& Ar, Data::FByteProperty& Value)
    {
        Ar >> Value.Enum;

        return Ar;
    }

    FArchive& operator>>(FArchive& Ar, Data::FClassProperty& Value)
    {
        Ar >> Value.MetaClass;

        return Ar;
    }

    FArchive& operator>>(FArchive& Ar, Data::FDelegateProperty& Value)
    {
        Ar >> Value.SignatureFunction;

        return Ar;
    }

    FArchive& operator>>(FArchive& Ar, Data::FEnumProperty& Value)
    {
        Ar >> Value.Enum;
        Value.UnderlyingProp = FProperty::SerializeSingleField(Ar);

        return Ar;
    }

    FArchive& operator>>(FArchive& Ar, Data::FFieldPathProperty& Value)
    {
        Ar >> Value.PropertyClass;

        return Ar;
    }

    FArchive& operator>>(FArchive& Ar, Data::FFloatProperty& Value)
    {
        return Ar;
    }

    FArchive& operator>>(FArchive& Ar, Data::FInt16Property& Value)
    {
        return Ar;
    }

    FArchive& operator>>(FArchive& Ar, Data::FInt64Property& Value)
    {
        return Ar;
    }

    FArchive& operator>>(FArchive& Ar, Data::FInt8Property& Value)
    {
        return Ar;
    }

    FArchive& operator>>(FArchive& Ar, Data::FIntProperty& Value)
    {
        return Ar;
    }

    FArchive& operator>>(FArchive& Ar, Data::FInterfaceProperty& Value)
    {
        Ar >> Value.InterfaceClass;

        return Ar;
    }

    FArchive& operator>>(FArchive& Ar, Data::FMapProperty& Value)
    {
        Value.KeyProp = FProperty::SerializeSingleField(Ar);
        Value.ValueProp = FProperty::SerializeSingleField(Ar);

        return Ar;
    }

    FArchive& operator>>(FArchive& Ar, Data::FMulticastDelegateProperty& Value)
    {
        Ar >> Value.SignatureFunction;

        return Ar;
    }

    FArchive& operator>>(FArchive& Ar, Data::FMulticastInlineDelegateProperty& Value)
    {
        Ar >> Value.SignatureFunction;

        return Ar;
    }

    FArchive& operator>>(FArchive& Ar, Data::FNameProperty& Value)
    {
        return Ar;
    }

    FArchive& operator>>(FArchive& Ar, Data::FObjectProperty& Value)
    {
        Ar >> Value.PropertyClass;

        return Ar;
    }

    FArchive& operator>>(FArchive& Ar, Data::FSetProperty& Value)
    {
        Value.ElementProp = FProperty::SerializeSingleField(Ar);

        return Ar;
    }

    FArchive& operator>>(FArchive& Ar, Data::FSoftClassProperty& Value)
    {
        Ar >> Value.PropertyClass;
        Value.MetaClass = FProperty::SerializeSingleField(Ar);

        return Ar;
    }

    FArchive& operator>>(FArchive& Ar, Data::FSoftObjectProperty& Value)
    {
        Ar >> Value.PropertyClass;

        return Ar;
    }

    FArchive& operator>>(FArchive& Ar, Data::FStrProperty& Value)
    {
        return Ar;
    }

    FArchive& operator>>(FArchive& Ar, Data::FStructProperty& Value)
    {
        Ar >> Value.Struct;

        return Ar;
    }

    FArchive& operator>>(FArchive& Ar, Data::FTextProperty& Value)
    {
        return Ar;
    }

    FArchive& operator>>(FArchive& Ar, Data::FUInt16Property& Value)
    {
        return Ar;
    }

    FArchive& operator>>(FArchive& Ar, Data::FUInt32Property& Value)
    {
        return Ar;
    }

    FArchive& operator>>(FArchive& Ar, Data::FUInt64Property& Value)
    {
        return Ar;
    }

}