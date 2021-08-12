#include "PakReader.h"

#include "../Objects/Core/Serialization/FByteArchive.h"
#include "../Objects/PakFile/FPakEntryLocation.h"
#include "../Objects/PakFile/FPakArchive.h"
#include "../Vfs/Vfs.h"
#include "../Align.h"

namespace upp::Readers {
    using namespace Objects;

    PakReader::PakReader(Objects::FArchive& Archive, const IKeyChain& KeyChain, uint32_t ReaderIdx) :
        BaseReader(Archive, KeyChain, ReaderIdx)
    {
        EPakVersion Version = EPakVersion::Latest;
        size_t PrevFooterSize = 0;
        do {
            size_t FooterSize = FPakInfo::GetSerializedSize(Version);
            if (FooterSize != PrevFooterSize) {
                PrevFooterSize = FooterSize;
                Ar.Seek(-FooterSize, ESeekDir::End);
                Ar >> Info;
                if (Info.Magic != 0) {
                    break;
                }
            }

            Version = EPakVersion((int32_t)Version - 1);
        } while (Version >= EPakVersion::Initial);
        
        if (Info.Magic == 0) {
            SetError(Error::InvalidFooter);
            return;
        }
        if (Info.Version == EPakVersion::FrozenIndex) {
            SetError(Error::UnsupportedFrozenIndex);
            return;
        }
        if (Info.Version > EPakVersion::Latest) {
            // Version is newer than supported, continuing
        }

        if (Info.Version >= EPakVersion::PathHashIndex) {
            ReadIndex();
        }
        else {
            ReadIndexLegacy();
        }
    }

    const FPakInfo& PakReader::GetPakInfo() const
    {
        return Info;
    }

    CompressionMethod PakReader::GetCompressionMethod(uint32_t CompressionMethodIdx) const
    {
        if (CompressionMethodIdx > Info.CompressionMethods.size()) {
            // Invalid idx
            return CompressionMethod::None;
        }

        switch (Crc32<true>(Info.CompressionMethods[CompressionMethodIdx])) {
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

    std::unique_ptr<FArchive> PakReader::OpenFile(uint32_t FileIdx)
    {
        if (EntryData.valueless_by_exception()) {
            return nullptr;
        }
        
        if (auto Data = std::get_if<std::vector<Objects::FPakEntry>>(&EntryData)) {
            return std::make_unique<FPakArchive>(Data->at(FileIdx), *this);
        }
        else {
            return std::make_unique<FPakArchive>(DecodePakEntry(FileIdx), *this);
        }
    }

    std::unique_ptr<UPackage> PakReader::ExportPackage(uint32_t AssetIdx, Vfs::Vfs& Vfs)
    {
        return nullptr;
    }

    std::unique_ptr<Objects::UPackage> PakReader::ExportPackageMinimal(uint32_t AssetIdx, Vfs::Vfs& Vfs)
    {
        return nullptr;
    }

    void PakReader::Append(Vfs::Vfs& Vfs, bool TranslatePaths)
    {
        if (HasError()) {
            return;
        }

        MergeDirectory(Vfs, TranslatePaths, std::move(Index));
    }

    const Objects::FAESSchedule& PakReader::GetSchedule() const
    {
        return KeyChain.GetKey(Info.EncryptionKeyGuid);
    }

    std::unique_ptr<char[]> PakReader::GetIndexArchive(int64_t Offset, int64_t Size, const FSHAHash& Hash)
    {
        auto Data = std::make_unique<char[]>(Size);
        Ar.PRead(Data.get(), Size, Offset);

        if (Info.IsEncryptedIndex) {
            auto& Schedule = GetSchedule();
            if (!Schedule.IsValid()) {
                SetError(Error::InvalidAesKey);
                return {};
            }

            Schedule.DecryptInPlace(Data.get(), Size);
        }

        if (!Hash.VerifyBuffer(Data.get(), Size)) {
            SetError(Error::InvalidIndexHash);
            return {};
        }

        return Data;
    }

    // https://github.com/EpicGames/UnrealEngine/blob/2bf1a5b83a7076a0fd275887b373f8ec9e99d431/Engine/Source/Runtime/PakFile/Private/IPlatformFilePak.cpp#L6020
    FPakEntry PakReader::DecodePakEntry(uint32_t Offset) const
    {
        FPakEntry Entry;
        char* Ptr = std::get<std::unique_ptr<char[]>>(EntryData).get() + Offset;

        uint32_t Val = *(uint32_t*)Ptr;
        Ptr += sizeof(uint32_t);

        Entry.CompressionMethodIndex = (Val >> 23) & 0x3F;

        // These bits check if the following field is 32-bit (0 if 64-bit)
        if (Val & (1 << 31)) {
            Entry.Offset = *(uint32_t*)Ptr;
            Ptr += sizeof(uint32_t);
        }
        else {
            Entry.Offset = *(int64_t*)Ptr;
            Ptr += sizeof(int64_t);
        }

        if (Val & (1 << 30)) {
            Entry.UncompressedSize = *(uint32_t*)Ptr;
            Ptr += sizeof(uint32_t);
        }
        else {
            Entry.UncompressedSize = *(int64_t*)Ptr;
            Ptr += sizeof(int64_t);
        }

        if (Entry.CompressionMethodIndex != 0) {
            // Size is only provided if there is compression
            if (Val & (1 << 29)) {
                Entry.Size = *(uint32_t*)Ptr;
                Ptr += sizeof(uint32_t);
            }
            else {
                Entry.Size = *(int64_t*)Ptr;
                Ptr += sizeof(int64_t);
            }
        }
        else {
            Entry.Size = Entry.UncompressedSize;
        }

        // Encoded entries are never marked as deleted, so only the encrypted flag is valid
        Entry.Flags = (Val & (1 << 22)) ? EPakEntryFlags::Encrypted : EPakEntryFlags::None;

        uint32_t CompressionBlockCount = (Val >> 6) & 0xFFFF;

        if (CompressionBlockCount == 0) {
            Entry.CompressionBlockSize = 0;
        }
        else {
            Entry.CompressionBlockSize = Entry.UncompressedSize < 65536 ? (uint32_t)Entry.UncompressedSize : ((Val & 0x3F) << 11);

            Entry.CompressionBlocks.resize(CompressionBlockCount);
            int64_t BlockOffset = (Info.Version >= EPakVersion::RelativeChunkOffsets ? 0 : Entry.Offset) + Entry.GetSerializedSize(Info.Version);
            if (CompressionBlockCount == 1 && !Entry.IsEncrypted()) {
                auto& Block = Entry.CompressionBlocks[0];
                Block.CompressedStart = BlockOffset;
                Block.CompressedEnd = BlockOffset + Entry.Size;
            }
            else {
                uint64_t Alignment = Entry.IsEncrypted() ? 16 : 1;
                uint32_t* BlockSizePtr = (uint32_t*)Ptr;
                for (auto& Block : Entry.CompressionBlocks) {
                    Block.CompressedStart = BlockOffset;
                    Block.CompressedEnd = BlockOffset + *BlockSizePtr;

                    BlockOffset += upp::Align(*BlockSizePtr, Alignment);
                    ++BlockSizePtr;
                }
            }
        }

        return Entry;
    }

    // https://github.com/EpicGames/UnrealEngine/blob/2bf1a5b83a7076a0fd275887b373f8ec9e99d431/Engine/Source/Runtime/PakFile/Private/IPlatformFilePak.cpp#L5117
    void PakReader::ReadIndex()
    {
        auto IndexData = GetIndexArchive(Info.IndexOffset, Info.IndexSize, Info.IndexHash);
        if (!IndexData) {
            return;
        }
        FByteArchive IndexAr(std::move(IndexData), Info.IndexSize, Ar.GetName() + " Index");

        std::string MountPoint;
        IndexAr >> MountPoint;
        ValidateMountPoint(MountPoint);

        int NumEntries;
        IndexAr >> NumEntries;

        uint64_t PathHashSeed;
        IndexAr >> PathHashSeed;

        int HasPathHashIndex;
        IndexAr >> HasPathHashIndex;
        int64_t PathHashIndexOffset;
        int64_t PathHashIndexSize;
        FSHAHash PathHashIndexHash;
        if (HasPathHashIndex) {
            IndexAr >> PathHashIndexOffset;
            IndexAr >> PathHashIndexSize;
            IndexAr >> PathHashIndexHash;
        }

        int HasFullDirectoryIndex;
        int64_t FullDirectoryIndexOffset;
        int64_t FullDirectoryIndexSize;
        FSHAHash FullDirectoryIndexHash;
        IndexAr >> HasFullDirectoryIndex;
        if (HasFullDirectoryIndex) {
            IndexAr >> FullDirectoryIndexOffset;
            IndexAr >> FullDirectoryIndexSize;
            IndexAr >> FullDirectoryIndexHash;
        }
        else {
            SetError(Error::MissingFullDirectoryIndex);
            return;
        }

        auto& EncodedPakEntries = EntryData.emplace<std::unique_ptr<char[]>>();
        IndexAr >> EncodedPakEntries;

        int FilesNum;
        IndexAr >> FilesNum;
        if (FilesNum > 0) {
            // TODO: Read (FilesNum) FPakEntries to the Entries vector
        }

        // We don't care about the path hashes (it's just a map between hashes and an index to the corresponding path)
        // As such, we don't need the pruned directory index either (we want the full one)

        auto FullDirectoryData = GetIndexArchive(FullDirectoryIndexOffset, FullDirectoryIndexSize, FullDirectoryIndexHash);
        if (!FullDirectoryData) {
            return;
        }
        FByteArchive FullDirectoryIndexAr(std::move(FullDirectoryData), FullDirectoryIndexSize, Ar.GetName() + " Directory Index");

        std::vector<std::pair<std::string, std::vector<std::pair<std::string, FPakEntryLocation>>>> DirIdx;
        FullDirectoryIndexAr >> DirIdx;

        auto& MountDir = Index.CreateDirectories<false>(MountPoint.c_str() + 1);
        for (auto& Dir : DirIdx) {
            if (Dir.second.empty()) {
                continue;
            }
            auto& VfsDir = Dir.first == "/" ? MountDir : MountDir.CreateDirectories<true>(Dir.first.c_str());
            for (auto& File : Dir.second) {
                VfsDir.CreateFile<false>(File.first.c_str(), File.first.size(), Vfs::File(GetReaderIdx(), File.second.Index));
            }
        }
    }

    void PakReader::ReadIndexLegacy()
    {
        auto IndexData = GetIndexArchive(Info.IndexOffset, Info.IndexSize, Info.IndexHash);
        if (!IndexData) {
            return;
        }
        FByteArchive IndexAr(std::move(IndexData), Info.IndexSize, Ar.GetName() + " Index");

        std::string MountPoint;
        IndexAr >> MountPoint;
        ValidateMountPoint(MountPoint);

        int NumEntries;
        IndexAr >> NumEntries;

        auto& MountDir = Index.CreateDirectories<true>(MountPoint.c_str() + 1);

        auto& Entries = EntryData.emplace<std::vector<Objects::FPakEntry>>();
        Entries.resize(NumEntries);
        for (int Idx = 0; Idx < NumEntries; ++Idx) {
            std::string Filename;
            FPakEntry Entry;
            IndexAr >> Filename;
            Entries[Idx].Serialize(IndexAr, Info.Version);

            MountDir.CreateFileAtPath<true>(Filename.c_str(), Vfs::File(GetReaderIdx(), Idx));
        }
    }
}