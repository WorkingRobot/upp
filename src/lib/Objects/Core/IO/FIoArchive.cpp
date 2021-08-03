#include "FIoArchive.h"

#include "../../../Align.h"

namespace upp::Objects {
    FIoArchive::FIoArchive(uint32_t ChunkIdx, Readers::IoReader& Reader) :
        FArchive(Reader.GetArchive().GetName() + " - Chunk " + std::to_string(ChunkIdx)),
        Reader(Reader),
        ChunkIdx(ChunkIdx),
        CachedBlockIdx(0xFFFFFFFF),
        CachedBlockSize(0),
        CompBufferSize(0),
        Position(0)
    {
        EnsureCompBufferSize(Reader.CompressionBlockSize);
    }

    size_t FIoArchive::Read(char* Data, size_t Size)
    {
        if (Position + Size > this->Size()) [[unlikely]] {
            Size = this->Size() - Position;
        }
        Read(Data, Size, Position);
        Position += Size;
        return Size;
    }

    size_t FIoArchive::Size() const
    {
        return GetLength();
    }

    size_t FIoArchive::Tell() const
    {
        return Position;
    }

    size_t FIoArchive::Seek(ptrdiff_t Offset, ESeekDir Direction)
    {
        switch (Direction)
        {
        case ESeekDir::Beg:
            return Position = Offset;
        case ESeekDir::Cur:
            return Position += Offset;
        case ESeekDir::End:
            return Position = Size() + Offset;
        default:
            return Position;
        }
    }

    size_t FIoArchive::PRead(char* Data, size_t Size, size_t Offset)
    {
        if (Offset + Size > this->Size()) [[unlikely]] {
            Size = this->Size() - Offset;
        }
        Read(Data, Size, Offset);
        return Size;
    }

    uint64_t FIoArchive::GetOffset() const
    {
        return Reader.ChunkOffsetLengths[ChunkIdx].GetOffset();
    }

    uint64_t FIoArchive::GetLength() const
    {
        return Reader.ChunkOffsetLengths[ChunkIdx].GetLength();
    }

    void FIoArchive::EnsureCompBufferSize(uint32_t MinSize)
    {
        if (MinSize > CompBufferSize) {
            CompBuffer = std::make_unique<char[]>(MinSize);
            CompBufferSize = MinSize;
        }
    }

    void FIoArchive::EnsureCachedBlockBufferSize(uint32_t MinSize)
    {
        if (MinSize > CachedBlockSize) {
            CachedBlockBuffer = std::make_unique<char[]>(MinSize);
            CachedBlockSize = MinSize;
        }
    }

    void FIoArchive::Read(char* Data, size_t Size, size_t DesiredOffset)
    {
        DesiredOffset += GetOffset();

        uint32_t CompressionBlockIdx = DesiredOffset / Reader.CompressionBlockSize;
        size_t BlockCopyStart = DesiredOffset % Reader.CompressionBlockSize;

        auto& Ar = Reader.Ar;

        while (Size > 0) {
            auto& Block = Reader.CompressionBlocks[CompressionBlockIdx];
            auto Method = Reader.GetCompressionMethod(Block.GetCompressionMethodIndex());

            int64_t BlockCopyCount = std::min(Block.GetUncompressedSize() - BlockCopyStart, Size);

            if (CachedBlockIdx == CompressionBlockIdx) {
                memcpy(Data, CachedBlockBuffer.get() + BlockCopyStart, BlockCopyCount);
            }
            else {
                int64_t EncryptionSize = Align<16>(Block.GetCompressedSize());

                EnsureCompBufferSize(EncryptionSize);

                auto PartitionIdx = Block.GetOffset() / Reader.PartitionSize;
                auto PartitionOffset = Block.GetOffset() % Reader.PartitionSize;
                if (PartitionIdx != 0) {
                    printf("nonzero partition offset!\n");
                }
                Ar.PRead(CompBuffer.get(), EncryptionSize, PartitionOffset);

                if ((uint8_t)Reader.ContainerFlags & (uint8_t)EIoContainerFlags::Encrypted) {
                    Reader.GetSchedule().DecryptInPlace(CompBuffer.get(), EncryptionSize);
                }

                if (BlockCopyStart == 0 && Size >= Block.GetUncompressedSize()) {
                    Compression::Decompress(Method, CompBuffer.get(), Block.GetCompressedSize(), Data, Block.GetUncompressedSize());

                    CachedBlockIdx = 0xFFFFFFFF;
                }
                else {
                    EnsureCachedBlockBufferSize(Block.GetUncompressedSize());

                    Compression::Decompress(Method, CompBuffer.get(), Block.GetCompressedSize(), CachedBlockBuffer.get(), Block.GetUncompressedSize());
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
}