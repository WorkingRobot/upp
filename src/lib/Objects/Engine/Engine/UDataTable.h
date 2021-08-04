#pragma once

#include "../../CoreUObject/UObject/UObject.h"
#include "ECurveTableMode.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/abee2073faa072b43e7ddb4dfe56299841cf9e42/Engine/Source/Runtime/Engine/Classes/Engine/Texture.h#L615
    struct UDataTable : public UObject {
        std::vector<std::pair<FName, UObject>> RowMap;

        UDataTable(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO);
    };
}