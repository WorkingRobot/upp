#include "FFileArchive.h"

namespace upp::Readers {
    FFileArchive::FFileArchive(const std::filesystem::path& Path, Versions::EGame Game) :
        FArchive(Game, GetPathSafe(Path).string())
    {
        File = fopen(Path.string().c_str(), "rb");
        if (!File) {
            SetError(Error::FileDoesNotExist);
        }
    }

    size_t FFileArchive::Read(char* Data, size_t Size)
    {
        return fread(Data, 1, Size, File);
    }

    size_t FFileArchive::Size() const
    {
        auto Pos = Tell();
        auto Ret = ((FFileArchive*)this)->Seek(0, SeekDir::End);
        ((FFileArchive*)this)->Seek(Pos, SeekDir::Beg);
        return Ret;
    }

    size_t FFileArchive::Tell() const
    {
        return _ftelli64(File);
    }

    size_t FFileArchive::Seek(ptrdiff_t Offset, SeekDir Direction)
    {
        if (_fseeki64(File, Offset, (int)Direction)) {
            SetError(Error::CannotSeek);
        }
        return Tell();
    }

    std::filesystem::path FFileArchive::GetPathSafe(const std::filesystem::path& Path)
    {
        std::error_code Error;
        auto AbsPath = std::filesystem::absolute(Path, Error);
        if (!Error) {
            return AbsPath;
        }
        return std::filesystem::path();
    }
}