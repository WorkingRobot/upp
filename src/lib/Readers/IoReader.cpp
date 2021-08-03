#include "IoReader.h"

#include "../Objects/Core/IO/FIoArchive.h"
#include "../Vfs/Vfs.h"
#include "../Align.h"

namespace upp::Readers {
    using namespace Objects;

    IoReader::IoReader(Objects::FArchive& Archive, Objects::FArchive& TocArchive, const IKeyChain& KeyChain, uint32_t ReaderIdx) :
        BaseReader(Archive, KeyChain, ReaderIdx)
    {
        FIoStoreTocResource Toc;
        auto Error = Toc.Serialize(TocArchive, KeyChain);
        if (Error != Error::None) {
            SetError(Error);
            return;
        }
        Construct(std::move(Toc));
    }

    IoReader::IoReader(Objects::FArchive& Archive, FIoStoreTocResource&& Toc, const IKeyChain& KeyChain, uint32_t ReaderIdx) :
        BaseReader(Archive, KeyChain, ReaderIdx)
    {
        Construct(std::move(Toc));
    }

    CompressionMethod IoReader::GetCompressionMethod(uint32_t CompressionMethodIdx) const
    {
        if (CompressionMethodIdx > CompressionMethods.size()) {
            // Invalid idx
            return CompressionMethod::None;
        }

        return CompressionMethods[CompressionMethodIdx];
    }

    bool IoReader::GetHeader(FContainerHeader& OutHeader)
    {
        auto HeaderIdx = GetChunkIdx(FIoChunkId(ContainerId.Id, 0, EIoChunkType::ContainerHeader));
        if (HeaderIdx == -1) {
            return false;
        }

        FIoArchive HeaderAr(HeaderIdx, *this);
        HeaderAr >> OutHeader;

        return true;
    }

    std::unique_ptr<FArchive> IoReader::OpenFile(uint32_t FileIdx)
    {
        if (ChunkOffsetLengths.empty()) {
            return nullptr;
        }
        
        return std::make_unique<FIoArchive>(FileIdx, *this);
    }

    void IoReader::Append(Vfs::Vfs& Vfs, bool TranslatePaths)
    {
        if (HasError()) {
            return;
        }

        // Only the global store does not have a container id attached
        if (ContainerId.IsValid()) {
            MergeDirectory(Vfs, TranslatePaths, std::move(Index));
        }
        else {
            auto NamesIdx = GetChunkIdx(FIoChunkId(0, 0, EIoChunkType::LoaderGlobalNames));
            auto HashesIdx = GetChunkIdx(FIoChunkId(0, 0, EIoChunkType::LoaderGlobalNameHashes));
            auto MetaIdx = GetChunkIdx(FIoChunkId(0, 0, EIoChunkType::LoaderInitialLoadMeta));
            if (NamesIdx != -1 && HashesIdx != -1 && MetaIdx != -1) {
                FIoArchive NamesAr(NamesIdx, *this);
                FIoArchive HashesAr(HashesIdx, *this);
                FIoArchive MetaAr(MetaIdx, *this);
                Vfs.GetGlobalData().Initialize(NamesAr, HashesAr, MetaAr);
            }
            else {
                // Not a true global store
            }
        }
    }

    void IoReader::Construct(FIoStoreTocResource&& Toc)
    {
        if (!Toc.Header.Magic.IsValid()) {
            SetError(Error::InvalidTocHeader);
            return;
        }

        EncryptionKeyGuid = Toc.Header.EncryptionKeyGuid;
        CompressionMethods.reserve(Toc.CompressionMethods.size());
        std::transform(Toc.CompressionMethods.begin(), Toc.CompressionMethods.end(), std::back_inserter(CompressionMethods), [](const std::string& Method) {
            switch (Crc32(Method)) {
            case Crc32("None"):
                return CompressionMethod::None;
            case Crc32("Zlib"):
                return CompressionMethod::Zlib;
            case Crc32("Gzip"):
                return CompressionMethod::Gzip;
            case Crc32("Oodle"):
                return CompressionMethod::Oodle;
            default:
                // Unknown/unsupported method
                return CompressionMethod::None;
            }
        });
        ChunkOffsetLengths = std::move(Toc.ChunkOffsetLengths);
        ChunkIds = std::move(Toc.ChunkIds);
        CompressionBlocks = std::move(Toc.CompressionBlocks);
        CompressionBlockSize = Toc.Header.CompressionBlockSize;
        PartitionSize = Toc.Header.PartitionSize;
        ContainerFlags = Toc.Header.ContainerFlags;
        ContainerId = Toc.Header.ContainerId;

        if ((uint8_t)Toc.Header.ContainerFlags & (uint8_t)EIoContainerFlags::Indexed && Toc.Header.DirectoryIndexSize != 0) {
            auto& Index = Toc.DirectoryIndex;
            ValidateMountPoint(Index.MountPoint);

            auto& MountDir = this->Index.CreateDirectories<false>(Index.MountPoint.c_str() + 1);

            Append(Index, MountDir, Index.DirectoryEntries[0].FirstChildEntry);
        }
    }

    const Objects::FAESSchedule& IoReader::GetSchedule() const
    {
        return KeyChain.GetKey(EncryptionKeyGuid);
    }

    uint32_t IoReader::GetChunkIdx(const Objects::FIoChunkId& Id) const
    {
        auto Itr = std::find(ChunkIds.begin(), ChunkIds.end(), Id);
        if (Itr != ChunkIds.end()) {
            return std::distance(ChunkIds.begin(), Itr);
        }
        return -1;
    }

    void IoReader::Append(const FIoDirectoryIndexResource& Index, Vfs::Directory<>& Tree, uint32_t DirIdx)
    {
        while (DirIdx != -1) {
            auto& Dir = Index.DirectoryEntries[DirIdx];
            auto& DirName = Index.StringTable[Dir.Name];
            auto& DirTree = Tree.CreateDirectory<false>(DirName.c_str(), DirName.size());

            uint32_t FileIdx = Dir.FirstFileEntry;
            while (FileIdx != -1) {
                auto& File = Index.FileEntries[FileIdx];
                auto& FileName = Index.StringTable[File.Name];
                DirTree.CreateFile<false>(FileName.c_str(), FileName.size(), Vfs::File(GetReaderIdx(), File.UserData));

                FileIdx = File.NextFileEntry;
            }

            Append(Index, DirTree, Dir.FirstChildEntry);

            DirIdx = Dir.NextSiblingEntry;
        }
    }
}