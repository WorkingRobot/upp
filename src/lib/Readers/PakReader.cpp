#include "PakReader.h"

#include "../Objects/Core/Serialization/FByteArchive.h"
#include "../Objects/PakFile/FPakEntryLocation.h"

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

    void PakReader::Append(Vfs::BaseVfs& Vfs)
    {
        if (HasError()) {
            return;
        }
    }

    std::unique_ptr<char[]> PakReader::GetIndexArchive(int64_t Offset, int64_t Size, const FSHAHash& Hash)
    {
        auto Data = std::make_unique<char[]>(Size);
        Ar.Seek(Offset, ESeekDir::Beg);
        Ar.Read(Data.get(), Size);

        if (Info.IsEncryptedIndex) {
            auto& Schedule = KeyChain.GetKey(Info.EncryptionKeyGuid);
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
        if (!ValidateMountPoint(MountPoint)) {
            printf("Bad mount point, mounting to root\n");
        }
        CompactFilePath(MountPoint);

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

        auto& MountDir = Index.CreateDirectories<true>(MountPoint.c_str() + 1);
        for (auto& Dir : DirIdx) {
            if (Dir.second.empty()) {
                continue;
            }
            auto& VfsDir = MountDir.CreateDirectories<true>(Dir.first.c_str());
            for (auto& File : Dir.second) {
                VfsDir.CreateFileAtPath<true>(File.first.c_str(), Vfs::File(GetReaderIdx(), File.second.Index));
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
        int NumEntries;
        IndexAr >> MountPoint;
        IndexAr >> NumEntries;

        if (!ValidateMountPoint(MountPoint)) {
            printf("Bad mount point, mounting to root\n");
        }

        CompactFilePath(MountPoint);

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