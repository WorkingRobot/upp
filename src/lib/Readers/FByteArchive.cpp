#include "FByteArchive.h"

namespace upp::Readers {
    FByteArchive::FByteArchive(std::unique_ptr<char[]>&& Data, size_t DataSize, Versions::EGame Game, const std::string& Name) :
        FArchive(Game, Name),
        Data(std::move(Data)),
        DataSize(DataSize)
    {
    }

    size_t FByteArchive::Read(char* Data, size_t Size)
    {
        if (Position + Size > DataSize) {
            Size = DataSize - Tell();
        }
        memcpy(Data, this->Data.get() + Tell(), Size);
        Position += Size;
        return Size;
    }

    size_t FByteArchive::Size() const
    {
        return DataSize;
    }

    size_t FByteArchive::Tell() const
    {
        return Position;
    }

    size_t FByteArchive::Seek(ptrdiff_t Offset, SeekDir Direction)
    {
        switch (Direction)
        {
        case SeekDir::Beg:
            return Position = Offset;
        case SeekDir::Cur:
            return Position += Offset;
        case SeekDir::End:
            return Position = DataSize + Offset;
        default:
            return Position;
        }
    }
}