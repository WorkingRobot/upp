#pragma once

#include "Properties/BaseProperty.h"

#include <variant>

namespace upp::Objects {
    struct FPropertyData {
        std::variant<
            std::monostate,
            ByteProperty,
            BoolProperty,
            IntProperty,
            FloatProperty,
            ObjectProperty,
            NameProperty,
            DelegateProperty,
            DoubleProperty,
            ArrayProperty,
            StructProperty,
            StrProperty,
            TextProperty,
            InterfaceProperty,
            MulticastDelegateProperty,
            WeakObjectProperty,
            LazyObjectProperty,
            AssetObjectProperty,
            SoftObjectProperty,
            UInt64Property,
            UInt32Property,
            UInt16Property,
            Int64Property,
            Int16Property,
            Int8Property,
            MapProperty,
            SetProperty,
            EnumProperty,
            FieldPathProperty
        > Data;

        FPropertyData(FArchive& Ar, const FPropertyTag& Tag, EReadType ReadType)
        {
            Construct(Ar, Tag, ReadType);
        }

        void Construct(FArchive& Ar, const FPropertyTag& Tag, EReadType ReadType);
    };
}