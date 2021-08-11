#include "FDuplicatedVerticesBuffer.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FDuplicatedVerticesBuffer& Value)
    {
        // https://github.com/EpicGames/UnrealEngine/blob/39a69dbfd7d3dead7de7c30da46fa5feb6ae1416/Engine/Source/Runtime/Core/Public/Containers/DynamicRHIResourceArray.h#L136
        // Serialize() on a TSkeletalMeshVertexData<> calls BulkSerialize
        // operator<< calls << on the Super class (TArray)
        Ar >> Value.DupVertData;
        Ar >> Value.DupVertIndexData;

        return Ar;
    }
}