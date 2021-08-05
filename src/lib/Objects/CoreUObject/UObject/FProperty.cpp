#include "FProperty.h"

namespace upp::Objects {
    FProperty::FProperty(FArchive& Ar, const std::string& Type) :
        Data(Construct(Ar, Type))
    {

    }

    std::unique_ptr<FProperty> FProperty::SerializeSingleField(FArchive& Ar)
    {
        FName PropertyTypeName;
        Ar >> PropertyTypeName;

        return std::make_unique<FProperty>(Ar, PropertyTypeName);
    }

    FPropertyData FProperty::Construct(FArchive& Ar, const std::string& Type)
    {
        // FField Members
        Ar >> Name;
        Ar >> Flags;

        // FProperty Members
        Ar >> ArrayDim;
        Ar >> ElementSize;
        Ar >> PropertyFlags;
        Ar >> RepIndex;
        Ar >> RepNotifyFunc;
        Ar >> BlueprintReplicationCondition;

        return FPropertyData(Ar, Type);
    }
}