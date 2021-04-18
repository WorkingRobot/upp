#include "FPakArchive.h"

#include "FPakArchiveReader.h"

namespace upp::Objects {
    FPakArchive::FPakArchive(const FPakEntry& Entry, Readers::PakReader& Reader) :
        FArchive(Reader.GetArchive().GetName() + " - Entry @ " + std::to_string(Entry.Offset)),
        Position(0)
    {
        if (Entry.CompressionMethodIndex != 0 && Reader.GetPakInfo().Version >= EPakVersion::CompressionEncryption) {
            if (Entry.IsEncrypted()) {
                Impl = std::make_unique<FPakArchiveReaderCompressed<FPakArchiveSimpleEncryption>>(Entry, Reader);
            }
            else {
                Impl = std::make_unique<FPakArchiveReaderCompressed<FPakArchiveNoEncryption>>(Entry, Reader);
            }
        }
        else if (Entry.IsEncrypted()) {
            Impl = std::make_unique<FPakArchiveReader<FPakArchiveSimpleEncryption>>(Entry, Reader);
        }
        else {
            Impl = std::make_unique<FPakArchiveReader<FPakArchiveNoEncryption>>(Entry, Reader);
        }
    }

    size_t FPakArchive::Read(char* Data, size_t Size)
    {
        if (Position + Size > Impl->Size()) {
            Size = Impl->Size() - Position;
        }
        Impl->Read(Data, Size, Position);
        Position += Size;
        return Size;
    }

    size_t FPakArchive::Size() const
    {
        return Impl->Size();
    }

    size_t FPakArchive::Tell() const
    {
        return Position;
    }

    size_t FPakArchive::Seek(ptrdiff_t Offset, ESeekDir Direction)
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
}