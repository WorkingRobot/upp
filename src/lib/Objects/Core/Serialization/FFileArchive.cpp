#include "FFileArchive.h"

namespace upp::Objects {
    FFileArchive::FFileArchive(const std::filesystem::path& Path) :
        FArchive(GetPathSafe(Path).string())
    {
        File = fopen(Path.string().c_str(), "rb");
    }

    FFileArchive::~FFileArchive()
    {
        if (IsValid()) {
            fclose(File);
        }
    }

    bool FFileArchive::IsValid() const
    {
        return File != nullptr;
    }

    size_t FFileArchive::Read(char* Data, size_t Size)
    {
        return fread(Data, 1, Size, File);
    }

    size_t FFileArchive::Size() const
    {
        auto Pos = Tell();
        auto Ret = ((FFileArchive*)this)->Seek(0, ESeekDir::End);
        ((FFileArchive*)this)->Seek(Pos, ESeekDir::Beg);
        return Ret;
    }

    size_t FFileArchive::Tell() const
    {
        return _ftelli64(File);
    }

    size_t FFileArchive::Seek(ptrdiff_t Offset, ESeekDir Direction)
    {
        if (_fseeki64(File, Offset, (int)Direction)) {
            // Could not seek
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