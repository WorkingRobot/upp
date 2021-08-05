#pragma once

#include "ELifetimeCondition.h"
#include "EObjectFlags.h"
#include "EPropertyFlags.h"
#include "FPropertyData.h"

namespace upp::Objects {
    struct FProperty {
        // FField Members
        FName Name;
        EObjectFlags Flags;

        // FProperty Members
        int ArrayDim;
        int ElementSize;
        EPropertyFlags PropertyFlags;
        uint16_t RepIndex;
        FName RepNotifyFunc;
        ELifetimeCondition BlueprintReplicationCondition;

        FPropertyData Data;

        FProperty(FArchive& Ar, const std::string& Type);

        static std::unique_ptr<FProperty> SerializeSingleField(FArchive& Ar);

    private:
        FPropertyData Construct(FArchive& Ar, const std::string& Type);
    };
}