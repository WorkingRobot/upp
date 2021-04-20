#pragma once

#include "../../../Readers/IOReader.h"

namespace upp::Objects {
    class FIoArchive : public FArchive {
    public:
        FIoArchive(uint32_t ChunkIdx, Readers::IoReader& Reader);

        size_t Read(char* Data, size_t Size) override;

        size_t Size() const override;

        size_t Tell() const override;

        size_t Seek(ptrdiff_t Offset, ESeekDir Direction) override;

    private:
        uint64_t GetOffset() const;

        uint64_t GetLength() const;

        void EnsureCompBufferSize(uint32_t MinSize);

        void EnsureCachedBlockBufferSize(uint32_t MinSize);

        void Read(char* Data, size_t Size, size_t DesiredOffset);

        Readers::IoReader& Reader;
        uint32_t ChunkIdx;
        uint32_t CachedBlockIdx;
        std::unique_ptr<char[]> CachedBlockBuffer;
        std::unique_ptr<char[]> CompBuffer;
        uint32_t CachedBlockSize;
        uint32_t CompBufferSize;

        size_t Position;
    };
}