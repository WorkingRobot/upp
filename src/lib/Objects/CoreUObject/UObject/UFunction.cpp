#include "UFunction.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/CoreUObject/Private/UObject/Class.cpp#L5592
    UFunction::UFunction(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO) :
        UStruct(Ar, Schema, Ctx, IsCDO)
    {
        Ar >> FunctionFlags;

        if ((uint32_t)FunctionFlags & (uint32_t)EFunctionFlags::FUNC_Net) {
            uint16_t RepOffset;
            Ar >> RepOffset;
        }

        Ar >> EventGraphFunction;
        Ar >> EventGraphCallOffset;
    }
}