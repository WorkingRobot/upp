#pragma once

#include "../FSpeedTreeWind.h"
#include "../FStaticMeshOccluderData.h"
#include "../FStaticMeshRenderData.h"
#include "FStaticMaterial.h"
#include "UStreamableRenderAsset.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/048ce1606af8daff143a1e99255aca9c6f04d46c/Engine/Source/Runtime/Engine/Classes/Engine/StaticMesh.h#L504
    struct UStaticMesh : public UStreamableRenderAsset {
        FPackageIndex BodySetup;
        FPackageIndex NavCollision;
        FGuid LightingGuid;
        std::vector<FPackageIndex> Sockets;
        FStaticMeshRenderData RenderData;
        FStaticMeshOccluderData OccluderData;
        FSpeedTreeWind SpeedTreeWind;
        std::vector<FStaticMaterial> StaticMaterials;

        UStaticMesh(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO);
    };
}