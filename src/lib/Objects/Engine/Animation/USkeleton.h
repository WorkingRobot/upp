#pragma once

#include "../../CoreUObject/UObject/UObject.h"
#include "../FReferenceSkeleton.h"
#include "FReferencePose.h"
#include "FSmartNameContainer.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/adb0f8832c780488c0e4298a6af161881f95e33d/Engine/Source/Runtime/Engine/Classes/Animation/Skeleton.h#L277
    struct USkeleton : public UObject {
        FReferenceSkeleton ReferenceSkeleton;
        std::vector<std::pair<FName, FReferencePose>> AnimRetargetSources;
        FGuid Guid;
        FSmartNameContainer SmartNames;
        std::vector<FName> ExistingMarkerNames;

        USkeleton(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO);
    };
}