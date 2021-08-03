#pragma once

#include "FArchive.h"

#include <filesystem>
#include <stdio.h>

namespace upp::Objects {
    class FFileArchive : public FArchive {
    public:
        FFileArchive(const std::filesystem::path& Path);

        ~FFileArchive();

        bool IsValid() const;

        size_t Read(char* Data, size_t Size) override;

        size_t Size() const override;

        size_t Tell() const override;

        size_t Seek(ptrdiff_t Offset, ESeekDir Direction) override;

        size_t PRead(char* Data, size_t Size, size_t Offset) override;

    private:
        static std::filesystem::path GetPathSafe(const std::filesystem::path& Path);

        void* File;
    };
}