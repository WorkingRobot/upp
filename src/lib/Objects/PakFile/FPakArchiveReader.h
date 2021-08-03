#pragma once

#include "../../Align.h"
#include "../../Compression.h"
#include "../../Readers/PakReader.h"

namespace upp::Objects {
    class FPakArchiveReaderBase {
    public:
        FPakArchiveReaderBase(const FPakEntry& Entry, Readers::PakReader& PakFile) :
            Entry(Entry),
            PakFile(PakFile)
        {

        }

        virtual size_t Size() const = 0;

        virtual void Read(char* Data, size_t Size, size_t DesiredOffset) = 0;

    protected:
        size_t GetFileOffset() const {
            return Entry.Offset + Entry.GetSerializedSize(PakFile.GetPakInfo().Version);
        }

        const FAESSchedule& GetSchedule() const {
            return PakFile.GetSchedule();
        }

        FArchive& GetAr() {
            return PakFile.Ar;
        }

        Readers::PakReader& PakFile;
        FPakEntry Entry;
    };

    class FPakArchiveNoEncryption {
    public:
        static constexpr size_t Alignment = 1;

        static __forceinline size_t Align(size_t Size) {
            return Size;
        }

        static __forceinline void DecryptBlock(char* Data, size_t Size, const FAESSchedule& Schedule) {
            // Do nothing
        }
    };

    class FPakArchiveSimpleEncryption {
    public:
        static constexpr size_t Alignment = 16;

        static __forceinline size_t Align(size_t Size) {
            return upp::Align<Alignment>(Size);
        }

        static __forceinline void DecryptBlock(char* Data, size_t Size, const FAESSchedule& Schedule) {
            Schedule.DecryptInPlace(Data, Size);
        }
    };

    template<typename EncryptionImpl>
    class FPakArchiveReader : public FPakArchiveReaderBase {
    public:
        FPakArchiveReader(const FPakEntry& Entry, Readers::PakReader& PakFile) :
            FPakArchiveReaderBase(Entry, PakFile)
        {

        }

        size_t Size() const override {
            return Entry.Size;
        }

        void Read(char* Data, size_t Size, size_t DesiredOffset) override {
            static constexpr auto Alignment = EncryptionImpl::Alignment;
            static constexpr auto AlignmentMask = ~(Alignment - 1);

            auto& Ar = GetAr();
            // Offset is unaligned, read previous block and copy the data we want at the start
            if (EncryptionImpl::Align(DesiredOffset) != DesiredOffset) {
                auto Start = DesiredOffset & AlignmentMask;
                auto Offset = DesiredOffset - Start;
                auto CopySize = std::min(Alignment - Offset, Size);

                char CachedBlockBuffer[Alignment];
                Ar.PRead(CachedBlockBuffer, Alignment, GetFileOffset() + Start);
                EncryptionImpl::DecryptBlock(CachedBlockBuffer, Alignment, GetSchedule());
                memcpy(Data, CachedBlockBuffer + Offset, CopySize);

                Data += CopySize;
                DesiredOffset += CopySize;
                Size -= CopySize;
            }

            auto CopySize = Size & AlignmentMask;
            Ar.PRead(Data, CopySize, GetFileOffset() + DesiredOffset);
            EncryptionImpl::DecryptBlock(Data, CopySize, GetSchedule());
            Size -= CopySize;
            Data += CopySize;

            if (Size > 0) {
                char CachedBlockBuffer[Alignment];
                Ar.PRead(CachedBlockBuffer, Alignment, GetFileOffset() + DesiredOffset + CopySize);
                EncryptionImpl::DecryptBlock(CachedBlockBuffer, Alignment, GetSchedule());
                memcpy(Data, CachedBlockBuffer, Size);
            }
        }
    };

    class FPakCompressionScratchBuffer {
    public:
        size_t TempBufferSize;
        std::unique_ptr<char[]> CachedBlockBuffer;
        size_t ScratchBufferSize;
        std::unique_ptr<char[]> CompBuffer;

        uint32_t CachedBlockIdx;

        FPakCompressionScratchBuffer(size_t CompressionBlockSize, int64_t ScratchSize) :
            TempBufferSize(CompressionBlockSize),
            CachedBlockBuffer(std::make_unique<char[]>(TempBufferSize)),
            ScratchBufferSize(ScratchSize),
            CompBuffer(std::make_unique<char[]>(ScratchBufferSize)),
            CachedBlockIdx(0xFFFFFFFF)
        {

        }
    };

    template<typename EncryptionImpl>
    class FPakArchiveReaderCompressed : public FPakArchiveReaderBase {
    public:
        FPakArchiveReaderCompressed(const FPakEntry& Entry, Readers::PakReader& PakFile) :
            FPakArchiveReaderBase(Entry, PakFile),
            Method(PakFile.GetCompressionMethod(Entry.CompressionMethodIndex)),
            CachedBlockIdx(0xFFFFFFFF),
            CachedBlockBuffer(std::make_unique<char[]>(Entry.CompressionBlockSize)),
            CompBuffer(std::make_unique<char[]>(EncryptionImpl::Align(Compression::CompressBound(Method, Entry.CompressionBlockSize))))
        {
            if (!Compression::IsValid(Method)) {
                printf("Compression method %d is unsupported, data will be UB\n", (int)Method);
            }
        }

        size_t Size() const override {
            return Entry.UncompressedSize;
        }

        void Read(char* Data, size_t Size, size_t DesiredOffset) override {
            if (!Compression::IsValid(Method)) {
                return;
            }

            uint32_t CompressionBlockIdx = DesiredOffset / Entry.CompressionBlockSize;
            size_t BlockCopyStart = DesiredOffset % Entry.CompressionBlockSize;

            auto& Ar = GetAr();
            while (Size > 0) {
                auto& Block = Entry.CompressionBlocks[CompressionBlockIdx];
                size_t UncompressedPos = (size_t)CompressionBlockIdx * Entry.CompressionBlockSize;
                size_t CompressedBlockSize = Block.CompressedEnd - Block.CompressedStart;
                size_t UncompressedBlockSize = std::min<size_t>(Entry.UncompressedSize - UncompressedPos, Entry.CompressionBlockSize);

                if (CompressedBlockSize > UncompressedBlockSize) {
                    // bigger compressed, log something here (not an error, just verbose)
                }

                int64_t BlockCopyCount = std::min(UncompressedBlockSize - BlockCopyStart, Size);

                if (CachedBlockIdx == CompressionBlockIdx) {
                    memcpy(Data, CachedBlockBuffer.get() + BlockCopyStart, BlockCopyCount);
                }
                else {
                    int64_t EncryptionSize = EncryptionImpl::Align(CompressedBlockSize);
                    Ar.PRead(CompBuffer.get(), EncryptionSize, Block.CompressedStart + (PakFile.GetPakInfo().Version >= EPakVersion::RelativeChunkOffsets ? Entry.Offset : 0));

                    EncryptionImpl::DecryptBlock(CompBuffer.get(), EncryptionSize, GetSchedule());
                    if (BlockCopyStart == 0 && Size >= Entry.CompressionBlockSize) {
                        Compression::Decompress(Method, CompBuffer.get(), CompressedBlockSize, Data, UncompressedBlockSize);

                        CachedBlockIdx = 0xFFFFFFFF;
                    }
                    else {
                        Compression::Decompress(Method, CompBuffer.get(), CompressedBlockSize, CachedBlockBuffer.get(), UncompressedBlockSize);
                        memcpy(Data, CachedBlockBuffer.get() + BlockCopyStart, BlockCopyCount);

                        CachedBlockIdx = CompressionBlockIdx;
                    }
                }

                Data += BlockCopyCount;
                Size -= BlockCopyCount;
                BlockCopyStart = 0;
                ++CompressionBlockIdx;
            }
        }

    private:
        CompressionMethod Method;
        uint32_t CachedBlockIdx;
        std::unique_ptr<char[]> CachedBlockBuffer;
        std::unique_ptr<char[]> CompBuffer;
    };
}