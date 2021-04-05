#pragma once

#include "FArchive.h"

#include <filesystem>
#include <stdio.h>

namespace upp::Readers {
    class FFileArchive : public FArchive {
    public:
        FFileArchive(const std::filesystem::path& Path, Versions::EGame Game = Versions::EGame::UE4_Latest);

        size_t Read(char* Data, size_t Size) override;

        size_t Size() const override;

        size_t Tell() const override;

        size_t Seek(ptrdiff_t Offset, SeekDir Direction) override;

    private:
        static std::filesystem::path GetPathSafe(const std::filesystem::path& Path);

        FILE* File;
    };
}