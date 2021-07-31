#pragma once

#include "FPropertyData.h"

namespace upp::Objects {
    // Not a real UE class; used to hold properties for UObjects
    struct FProperty {
        FProperty(FArchive& Ar, const Providers::Property& PropertyInfo, EReadType ReadType);

        ~FProperty();

        FPropertyTag Tag;

        FPropertyData Data;
    };
}