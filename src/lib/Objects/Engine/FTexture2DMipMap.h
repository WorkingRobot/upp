#pragma once

#include "../Core/Serialization/FArchive.h"
#include "../CoreUObject/Serialization/FByteBulkData.h"
#include "../CoreUObject/UObject/FSerializeCtx.h"

namespace upp::Objects {
    struct FTexture2DMipMap {
        int SizeX;
        int SizeY;
        int SizeZ;
        FByteBulkData BulkData;

        void Serialize(FArchive& Ar, FSerializeCtx& Ctx);
    };
}