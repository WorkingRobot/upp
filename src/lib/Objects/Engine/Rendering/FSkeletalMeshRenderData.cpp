#include "FSkeletalMeshRenderData.h"

namespace upp::Objects {
    void FSkeletalMeshRenderData::Serialize(FArchive& Ar, FSerializeCtx& Ctx, bool HasVertexColors)
    {
        constexpr bool KeepMobileMinLODSettingOnDesktop = true;
        if constexpr (KeepMobileMinLODSettingOnDesktop) {
            int MinMobileLODIdx;
            Ar >> MinMobileLODIdx;
        }

        int SerializeNum;
        Ar >> SerializeNum;
        LODRenderData.reserve(SerializeNum);
        for (int Idx = 0; Idx < SerializeNum; ++Idx) {
            LODRenderData.emplace_back().Serialize(Ar, Ctx, HasVertexColors);
        }

        Ar >> NumInlinedLODs;
        Ar >> NumNonOptionalLODs;
    }
}