#include "FByteArchive.h"

namespace upp::Objects {
    FByteArchive::FByteArchive(std::unique_ptr<char[]>&& Data, size_t DataSize, const std::string& Name) :
        FArchive(Name),
        Data(std::move(Data)),
        DataSize(DataSize),
        Position(0)
    {
    }

    size_t FByteArchive::Read(char* Data, size_t Size)
    {
        if (Position + Size > DataSize) [[unlikely]] {
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

    size_t FByteArchive::Seek(ptrdiff_t Offset, ESeekDir Direction)
    {
        switch (Direction)
        {
        case ESeekDir::Beg:
            return Position = Offset;
        case ESeekDir::Cur:
            return Position += Offset;
        case ESeekDir::End:
            return Position = DataSize + Offset;
        default:
            return Position;
        }
    }

    size_t FByteArchive::PRead(char* Data, size_t Size, size_t Offset)
    {
        if (Offset + Size > DataSize) [[unlikely]] {
            Size = DataSize - Offset;
        }
        memcpy(Data, this->Data.get() + Offset, Size);
        return Size;
    }
}