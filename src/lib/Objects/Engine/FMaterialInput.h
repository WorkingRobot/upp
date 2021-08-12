#pragma once

#include "../Core/Math/FColor.h"
#include "../Core/Serialization/FArchive.h"
#include "FExpressionInput.h"

namespace upp::Objects {
    // Why it's not TMaterialInput is behind my understanding
    template<class T>
    struct FMaterialInput : public FExpressionInput {
        friend FArchive& operator>>(FArchive& Ar, FMaterialInput& Value)
        {
            Ar >> (FExpressionInput&)Value;

            // https://github.com/EpicGames/UnrealEngine/blob/1c009f0a52d36b7a097a75675589ef36da8ba5c4/Engine/Source/Runtime/Engine/Private/Materials/MaterialShared.cpp#L354
            int bTemp;
            Ar >> bTemp;
            T TempType;
            Ar >> TempType;

            return Ar;
        }
    };

    using FColorMaterialInput = FMaterialInput<FColor>;
}