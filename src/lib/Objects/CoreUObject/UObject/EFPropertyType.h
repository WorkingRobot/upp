#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class EFPropertyType : uint64_t {
        FArrayProperty,
        FBoolProperty,
        FByteProperty,
        FClassProperty,
        FDelegateProperty,
        FEnumProperty,
        FFieldPathProperty,
        FFloatProperty,
        FInt64Property,
        FInt16Property,
        FInt8Property,
        FIntProperty,
        FInterfaceProperty,
        FMapProperty,
        FMulticastDelegateProperty,
        FMulticastInlineDelegateProperty,
        FNameProperty,
        FObjectProperty,
        FSetProperty,
        FSoftClassProperty,
        FSoftObjectProperty,
        FStrProperty,
        FStructProperty,
        FTextProperty,
        FUInt16Property,
        FUInt32Property,
        FUInt64Property,

        Unknown = 0xFF
    };
}