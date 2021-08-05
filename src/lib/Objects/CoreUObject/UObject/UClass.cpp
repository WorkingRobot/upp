#include "UClass.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/CoreUObject/Private/UObject/Class.cpp#L5592
    UClass::UClass(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO) :
        UStruct(Ar, Schema, Ctx, IsCDO)
    {
        Ar >> FuncMap;
        Ar >> ClassFlags;

        Ar >> ClassWithin;
        Ar >> ClassConfigName;
        
        Ar >> ClassGeneratedBy;

        Ar >> Interfaces;

        int bDeprecatedForceScriptOrder;
        Ar >> bDeprecatedForceScriptOrder;

        FName Dummy;
        Ar >> Dummy;

        int bCooked;
        Ar >> bCooked;
        IsCooked = bCooked;

        Ar >> ClassDefaultObject;
    }
}