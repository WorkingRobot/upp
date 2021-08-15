#include "FPipelineFileCache.h"

#include "FPipelineCacheFileFormatHeader.h"

namespace upp::Objects {
    FPipelineFileCache::FPipelineFileCache(FArchive& Ar)
    {
        Ar >> *this;
    }

    constexpr uint64_t FileMagic = 0x5049504543414348; // PIPECACH (reversed because of little endian)
    constexpr auto FileVersion = EPipelineCacheFileFormatVersions::Supported;

    // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/RHI/Private/PipelineFileCache.cpp#L1428
    FArchive& operator>>(FArchive& Ar, FPipelineFileCache& Value)
    {
        FPipelineCacheFileFormatHeader Header;
        Ar >> Header;

        if (Header.Magic != FileMagic) {
            return Ar;
        }

        if (Header.Version != FileVersion) {
            return Ar;
        }

        Value.GameVersion = Header.GameVersion;
        Value.ShaderPlatform = Header.Platform;
        Value.FileGuid = Header.Guid;

        Ar.Seek(Header.TableOffset, ESeekDir::Beg);
        Ar >> Value.TOC;

        Value.Entries.reserve(Value.TOC.MetaData.size());
        for (auto& [PSOHash, Meta] : Value.TOC.MetaData) {
            Ar.Seek(Meta.FileOffset, ESeekDir::Beg);
            Ar >> Value.Entries.emplace_back();
#ifdef _DEBUG
            if (Ar.Tell() != Meta.FileOffset + Meta.FileSize) {
                _CrtDbgBreak();
            }
#endif
        }

        return Ar;
    }
}