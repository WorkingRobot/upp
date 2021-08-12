#include "FExpressionInput.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FExpressionInput& Value)
    {
        Ar >> Value.OutputIndex;
        Ar >> Value.InputName;

        int Temp;
        Ar >> Temp >> Temp >> Temp >> Temp >> Temp;

        // https://github.com/EpicGames/UnrealEngine/blob/1c009f0a52d36b7a097a75675589ef36da8ba5c4/Engine/Source/Runtime/Engine/Private/Materials/MaterialShared.cpp#L337
        // Technically only used in cooked builds, but you'd have bigger problems on your hands elsewhere in this lib if you didn't have a cooked build
        Ar >> Value.ExpressionName;

        return Ar;
    }
}