#pragma once

#include "IFileProvider.h"

#include <filesystem>

namespace upp::FileProvider {
    class DefaultFileProvider : public IFileProvider {
    public:
        DefaultFileProvider(const std::filesystem::path& Directory, UE4::Versions::EGame Game = UE4::Versions::EGame::UE4_Latest);
    };
}