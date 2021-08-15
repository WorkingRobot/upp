#include "FPipelineCacheFileFormatPSOMetaData.h"

#include "EPipelineCacheFileFormatVersions.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FPipelineCacheFileFormatPSOMetaData& Value)
    {
        Ar >> Value.FileOffset;
        Ar >> Value.FileSize;

        if constexpr (EPipelineCacheFileFormatVersions::Supported == EPipelineCacheFileFormatVersions::PatchSizeReduction_NoDuplicatedGuid) {
            bool ArchiveFileGuid;
            Ar >> ArchiveFileGuid;
            if (ArchiveFileGuid) {
                Ar >> Value.FileGuid;
            }
        }
        else {
            Ar >> Value.FileGuid;
        }

        Ar >> Value.Stats;

        if constexpr (EPipelineCacheFileFormatVersions::Supported == EPipelineCacheFileFormatVersions::LibraryID) {
            std::vector<uint32_t> IDs;
            Ar >> IDs;
        }

        if constexpr (EPipelineCacheFileFormatVersions::Supported >= EPipelineCacheFileFormatVersions::ShaderMetaData) {
            Ar >> Value.Shaders;
        }

        if constexpr (EPipelineCacheFileFormatVersions::Supported >= EPipelineCacheFileFormatVersions::PSOUsageMask) {
            Ar >> Value.UsageMask;
        }

        if constexpr (EPipelineCacheFileFormatVersions::Supported >= EPipelineCacheFileFormatVersions::EngineFlags) {
            Ar >> Value.EngineFlags;
        }

        Ar >> Value.LastUsedUnixTime;
        //if constexpr (EPipelineCacheFileFormatVersions::Supported >= EPipelineCacheFileFormatVersions::LastUsedTime) {
        //    Ar >> Value.LastUsedUnixTime;
        //}

        return Ar;
    }
}