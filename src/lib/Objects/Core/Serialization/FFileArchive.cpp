#include "FFileArchive.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

namespace upp::Objects {
    FFileArchive::FFileArchive(const std::filesystem::path& Path) :
        FArchive(GetPathSafe(Path).string()),
        File(INVALID_HANDLE_VALUE)
    {
        File = CreateFileW(Path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    }

    FFileArchive::~FFileArchive()
    {
        if (IsValid()) {
            CloseHandle(File);
        }
    }

    bool FFileArchive::IsValid() const
    {
        return File != INVALID_HANDLE_VALUE;
    }

    size_t FFileArchive::Read(char* Data, size_t Size)
    {
        DWORD Ret;
        return ReadFile(File, Data, Size, &Ret, NULL) ? Ret : 0;
    }

    size_t FFileArchive::Size() const
    {
        LARGE_INTEGER Ret;
        return GetFileSizeEx(File, &Ret) ? Ret.QuadPart : 0;
    }

    size_t FFileArchive::Tell() const
    {
        LARGE_INTEGER Ret;
        return SetFilePointerEx(File, {}, &Ret, FILE_CURRENT) ? Ret.QuadPart : 0;
    }

    size_t FFileArchive::Seek(ptrdiff_t Offset, ESeekDir Direction)
    {
        LARGE_INTEGER Ret;
        return SetFilePointerEx(File, { .QuadPart = Offset }, &Ret, (DWORD)Direction) ? Ret.QuadPart : 0;
    }

    size_t FFileArchive::PRead(char* Data, size_t Size, size_t Offset)
    {
        DWORD Ret;
        OVERLAPPED Ol{ .Offset = Offset & 0xFFFFFFFF, .OffsetHigh = Offset >> 32 & 0xFFFFFFFF };
        return ReadFile(File, Data, Size, &Ret, &Ol) ? Ret : 0;
    }

    std::filesystem::path FFileArchive::GetPathSafe(const std::filesystem::path& Path)
    {
        std::error_code Error;
        auto AbsPath = std::filesystem::absolute(Path, Error);
        return Error ? Path : AbsPath;
    }
}