#include "FStaticMeshRenderData.h"

#include "FStripDataFlags.h"

namespace upp::Objects {
    void FStaticMeshRenderData::Serialize(FArchive& Ar, FSerializeCtx& Ctx)
    {
        constexpr bool KeepMobileMinLODSettingOnDesktop = true;
        if constexpr (KeepMobileMinLODSettingOnDesktop) {
            int MinMobileLODIdx;
            Ar >> MinMobileLODIdx;
        }

        int SerializeNum;
        Ar >> SerializeNum;
        LODResources.reserve(SerializeNum);
        for (int Idx = 0; Idx < SerializeNum; ++Idx) {
            LODResources.emplace_back().Serialize(Ar, Ctx);
        }

        Ar >> NumInlinedLODs;

        constexpr uint8_t DistanceFieldDataStripFlag = 1;

        FStripDataFlags StripFlags;
        Ar >> StripFlags;
        if (!StripFlags.IsDataStrippedForServer() && !StripFlags.IsClassDataStripped(DistanceFieldDataStripFlag)) {
            for (auto& LOD : LODResources) {
                int bValid;
                Ar >> bValid;
                if (bValid) {
                    Ar >> LOD.DistanceFieldData;
                }
            }
        }

        Ar >> Bounds;
        int bLODsShareStaticLighting;
        Ar >> bLODsShareStaticLighting;
        LODsShareStaticLighting = bLODsShareStaticLighting;

        Ar >> ScreenSize;
    }
}