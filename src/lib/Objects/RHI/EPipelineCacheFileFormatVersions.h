#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class EPipelineCacheFileFormatVersions : uint32_t {
        FirstWorking = 7,
        LibraryID = 9,
        ShaderMetaData = 10,
        SortedVertexDesc = 11,
        TOCMagicGuard = 12,
        PSOUsageMask = 13,
        PSOBindCount = 14,
        EOFMarker = 15,
        EngineFlags = 16,
        Subpass = 17,
        PatchSizeReduction_NoDuplicatedGuid = 18,
        AlphaToCoverage = 19,
        AddingMeshShaders = 20,
        RemovingTessellationShaders = 21,
        LastUsedTime = 22,
        MoreRenderTargetFlags = 23,

        Supported = AddingMeshShaders
    };
}