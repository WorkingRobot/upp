#include "FFieldPath.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FFieldPath& Value)
    {
        // https://github.com/EpicGames/UnrealEngine/blob/8bcc8f7e4836f6449a86052b3502f79f42c6dba3/Engine/Source/Runtime/CoreUObject/Private/UObject/FieldPath.cpp#L350
        // ????
        Ar >> Value.Names;

        return Ar;
    }
}