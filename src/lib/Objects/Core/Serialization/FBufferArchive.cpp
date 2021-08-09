#include "FBufferArchive.h"

namespace upp::Objects {
    FBufferArchive::FBufferArchive(const char* Data, size_t DataSize, const std::string& Name) :
        FArchive(Name),
        Data(Data),
        DataSize(DataSize),
        Position(0)
    {
    }

    size_t FBufferArchive::Read(char* Data, size_t Size)
    {
        if (Position + Size > DataSize) [[unlikely]] {
            Size = DataSize - Tell();
        }
        memcpy(Data, this->Data + Tell(), Size);
        Position += Size;
        return Size;
    }

    size_t FBufferArchive::Size() const
    {
        return DataSize;
    }

    size_t FBufferArchive::Tell() const
    {
        return Position;
    }

    size_t FBufferArchive::Seek(ptrdiff_t Offset, ESeekDir Direction)
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

    size_t FBufferArchive::PRead(char* Data, size_t Size, size_t Offset)
    {
        if (Offset + Size > DataSize) [[unlikely]] {
            Size = DataSize - Offset;
        }
        memcpy(Data, this->Data + Offset, Size);
        return Size;
    }
}