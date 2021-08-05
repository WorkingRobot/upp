#pragma once

#include "EFPropertyType.h"
#include "FPackageIndex.h"

namespace upp::Objects {
    class FProperty;

    class FPropertyData {
        union DataUnion {
            struct FArrayProperty {
                std::unique_ptr<FProperty> Property;

                friend FArchive& operator>>(FArchive& Ar, FArrayProperty& Value);
            } Array;
            struct FBoolProperty {
                uint8_t FieldSize;
                uint8_t ByteOffset;
                uint8_t ByteMask;
                uint8_t FieldMask;
                uint8_t BoolSize;
                bool bIsNativeBool;

                friend FArchive& operator>>(FArchive& Ar, FBoolProperty& Value);
            } Bool;
            struct FByteProperty {
                FPackageIndex Enum;

                friend FArchive& operator>>(FArchive& Ar, FByteProperty& Value);
            } Byte;
            struct FClassProperty {
                FPackageIndex PropertyClass;
                FPackageIndex MetaClass;

                friend FArchive& operator>>(FArchive& Ar, FClassProperty& Value);
            } Class;
            struct FDelegateProperty {
                FPackageIndex SignatureFunction;

                friend FArchive& operator>>(FArchive& Ar, FDelegateProperty& Value);
            } Delegate;
            struct FEnumProperty {
                std::unique_ptr<FProperty> UnderlyingProp;
                FPackageIndex Enum;

                friend FArchive& operator>>(FArchive& Ar, FEnumProperty& Value);
            } Enum;
            struct FFieldPathProperty {
                FName PropertyClass;

                friend FArchive& operator>>(FArchive& Ar, FFieldPathProperty& Value);
            } FieldPath;
            struct FFloatProperty {
                friend FArchive& operator>>(FArchive& Ar, FFloatProperty& Value);
            } Float;
            struct FInt16Property {
                friend FArchive& operator>>(FArchive& Ar, FInt16Property& Value);
            } Int16;
            struct FInt64Property {
                friend FArchive& operator>>(FArchive& Ar, FInt64Property& Value);
            } Int64;
            struct FInt8Property {
                friend FArchive& operator>>(FArchive& Ar, FInt8Property& Value);
            } Int8;
            struct FIntProperty {
                friend FArchive& operator>>(FArchive& Ar, FIntProperty& Value);
            } Int;
            struct FInterfaceProperty {
                FPackageIndex InterfaceClass;

                friend FArchive& operator>>(FArchive& Ar, FInterfaceProperty& Value);
            } Interface;
            struct FMapProperty {
                std::unique_ptr<FProperty> KeyProp;
                std::unique_ptr<FProperty> ValueProp;

                friend FArchive& operator>>(FArchive& Ar, FMapProperty& Value);
            } Map;
            struct FMulticastDelegateProperty {
                FPackageIndex SignatureFunction;

                friend FArchive& operator>>(FArchive& Ar, FMulticastDelegateProperty& Value);
            } MulticastDelegate;
            struct FMulticastInlineDelegateProperty {
                FPackageIndex SignatureFunction;

                friend FArchive& operator>>(FArchive& Ar, FMulticastInlineDelegateProperty& Value);
            } MulticastInlineDelegate;
            struct FNameProperty {
                friend FArchive& operator>>(FArchive& Ar, FNameProperty& Value);
            } Name;
            struct FObjectProperty {
                FPackageIndex PropertyClass;

                friend FArchive& operator>>(FArchive& Ar, FObjectProperty& Value);
            } Object;
            struct FSetProperty {
                std::unique_ptr<FProperty> ElementProp;

                friend FArchive& operator>>(FArchive& Ar, FSetProperty& Value);
            } Set;
            struct FSoftClassProperty {
                FPackageIndex PropertyClass;
                std::unique_ptr<FProperty> MetaClass;

                friend FArchive& operator>>(FArchive& Ar, FSoftClassProperty& Value);
            } SoftClass;
            struct FSoftObjectProperty {
                FPackageIndex PropertyClass;

                friend FArchive& operator>>(FArchive& Ar, FSoftObjectProperty& Value);
            } SoftObject;
            struct FStrProperty {
                friend FArchive& operator>>(FArchive& Ar, FStrProperty& Value);
            } Str;
            struct FStructProperty {
                FPackageIndex Struct;

                friend FArchive& operator>>(FArchive& Ar, FStructProperty& Value);
            } Struct;
            struct FTextProperty {
                friend FArchive& operator>>(FArchive& Ar, FTextProperty& Value);
            } Text;
            struct FUInt16Property {
                friend FArchive& operator>>(FArchive& Ar, FUInt16Property& Value);
            } UInt16;
            struct FUInt32Property {
                friend FArchive& operator>>(FArchive& Ar, FUInt32Property& Value);
            } UInt32;
            struct FUInt64Property {
                friend FArchive& operator>>(FArchive& Ar, FUInt64Property& Value);
            } UInt64;

            DataUnion() {}
            ~DataUnion() {}
        } Data;

        EFPropertyType Type;

        void ConstructUnion();

        void DestructUnion();

    public:
        FPropertyData();

        FPropertyData(const FPropertyData& Other);

        FPropertyData(FPropertyData&& Other) noexcept;

        FPropertyData(FArchive& Ar, const std::string& Type);

        ~FPropertyData();

        EFPropertyType GetType() const;

        const DataUnion& GetData() const;

        DataUnion& GetData(EFPropertyType RequestedType);
    };
}