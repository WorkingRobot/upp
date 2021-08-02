#pragma once

#include "../../../Readers/Error.h"
#include "../../../IKeyChain.h"
#include "../Serialization/FArchive.h"
#include "../Misc/FSHAHash.h"
#include "FIoChunkId.h"
#include "FIoDirectoryIndexResource.h"
#include "FIoOffsetAndLength.h"
#include "FIoStoreTocCompressedBlockEntry.h"
#include "FIoStoreTocEntryMeta.h"
#include "FIoStoreTocHeader.h"

namespace upp::Objects {
    struct FIoStoreTocResource {
        FIoStoreTocHeader Header;

        std::vector<FIoChunkId> ChunkIds;

        std::vector<FIoOffsetAndLength> ChunkOffsetLengths;

        std::vector<FIoStoreTocCompressedBlockEntry> CompressionBlocks;

        std::vector<std::string> CompressionMethods;

        std::vector<FSHAHash> ChunkBlockSignatures;

        std::vector<FIoStoreTocEntryMeta> ChunkMetas;

        FIoDirectoryIndexResource DirectoryIndex;

        Readers::Error Serialize(FArchive& Ar, const IKeyChain& KeyChain);
    };
}