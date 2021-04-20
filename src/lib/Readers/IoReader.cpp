#include "IoReader.h"

#include "../Objects/Core/IO/FIoArchive.h"
#include "../Vfs/Vfs.h"
#include "../Align.h"

namespace upp::Readers {
    using namespace Objects;

    FIoStoreTocResource GetToc(Objects::FArchive& Ar, const IKeyChain& KeyChain) {
        FIoStoreTocResource Toc;
        Toc.Serialize(Ar, KeyChain);
        return Toc;
    }

    IoReader::IoReader(Objects::FArchive& Archive, Objects::FArchive& TocArchive, const IKeyChain& KeyChain, uint32_t ReaderIdx) :
        IoReader(Archive, GetToc(TocArchive, KeyChain), KeyChain, ReaderIdx)
    {

    }

    IoReader::IoReader(Objects::FArchive& Archive, FIoStoreTocResource&& Toc, const IKeyChain& KeyChain, uint32_t ReaderIdx) :
        BaseReader(Archive, KeyChain, ReaderIdx)
    {
        if (!Toc.Header.Magic.IsValid()) {
            SetError(Error::InvalidTocHeader);
            return;
        }

        EncryptionKeyGuid = Toc.Header.EncryptionKeyGuid;
        CompressionMethods = std::move(Toc.CompressionMethods);
        ChunkOffsetLengths = std::move(Toc.ChunkOffsetLengths);
        CompressionBlocks = std::move(Toc.CompressionBlocks);
        CompressionBlockSize = Toc.Header.CompressionBlockSize;
        PartitionSize = Toc.Header.PartitionSize;
        ContainerFlags = Toc.Header.ContainerFlags;

        auto& Index = Toc.DirectoryIndex;
        if (!ValidateMountPoint(Index.MountPoint)) {
            printf("Bad mount point, mounting to root\n");
        }
        CompactFilePath(Index.MountPoint);

        auto& MountDir = this->Index.CreateDirectories<false>(Index.MountPoint.c_str() + 1);

        Append(Index, MountDir, Index.DirectoryEntries[0].FirstChildEntry);
    }

    CompressionMethod IoReader::GetCompressionMethod(uint32_t CompressionMethodIdx) const
    {
        if (CompressionMethodIdx > CompressionMethods.size()) {
            // Invalid idx
            return CompressionMethod::None;
        }

        switch (Crc32<true>(CompressionMethods[CompressionMethodIdx])) {
        case Crc32<true>("None"):
            return CompressionMethod::None;
        case Crc32<true>("Zlib"):
            return CompressionMethod::Zlib;
        case Crc32<true>("Gzip"):
            return CompressionMethod::Gzip;
        case Crc32<true>("Oodle"):
            return CompressionMethod::Oodle;
        default:
            // Unknown/unsupported method
            return CompressionMethod::None;
        }
    }

    std::unique_ptr<FArchive> IoReader::OpenFile(uint32_t FileIdx)
    {
        if (ChunkOffsetLengths.empty()) {
            return nullptr;
        }
        
        return std::make_unique<FIoArchive>(FileIdx, *this);
    }

    void IoReader::Append(Vfs::Vfs& Vfs)
    {
        if (HasError()) {
            return;
        }

        Vfs.GetRootDirectory().MergeDirectory<true>(std::move(Index));
    }

    const Objects::FAESSchedule& IoReader::GetSchedule() const
    {
        return KeyChain.GetKey(EncryptionKeyGuid);
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