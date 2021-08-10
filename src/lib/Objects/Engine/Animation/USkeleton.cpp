#include "USkeleton.h"

#include "../FStripDataFlags.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/adb0f8832c780488c0e4298a6af161881f95e33d/Engine/Source/Runtime/Engine/Private/Animation/Skeleton.cpp#L187
    USkeleton::USkeleton(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO) :
        UObject(Ar, Schema, Ctx, IsCDO)
    {
        Ar >> ReferenceSkeleton;

        Ar >> AnimRetargetSources;

        Ar >> Guid;

        Ar >> SmartNames;

        FStripDataFlags StripFlags;
        Ar >> StripFlags;
        if (!StripFlags.IsEditorDataStripped()) {
            Ar >> ExistingMarkerNames;
        }
    }
}