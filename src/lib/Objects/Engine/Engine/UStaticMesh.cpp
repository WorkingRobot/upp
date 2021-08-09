#include "UStaticMesh.h"

#include "../FStripDataFlags.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/048ce1606af8daff143a1e99255aca9c6f04d46c/Engine/Source/Runtime/Engine/Private/StaticMesh.cpp#L4682
    UStaticMesh::UStaticMesh(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO) :
        UStreamableRenderAsset(Ar, Schema, Ctx, IsCDO)
    {
        FStripDataFlags StripFlags;
        Ar >> StripFlags;

        int bCooked;
        Ar >> bCooked;

        Ar >> BodySetup;

        Ar >> NavCollision;

        Ar >> LightingGuid;

        Ar >> Sockets;

        if (bCooked) {
            RenderData.Serialize(Ar, Ctx);
            Ar >> OccluderData;
        }
        
        int bHasSpeedTreeWind;
        Ar >> bHasSpeedTreeWind;

        if (bHasSpeedTreeWind) {
            Ar >> SpeedTreeWind;
        }

        Ar >> StaticMaterials;
    }
}