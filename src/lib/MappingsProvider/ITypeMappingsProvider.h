#pragma once

#include "../UE4/Versions/EGame.h"

#include <optional>
#include <string>

namespace upp::FileProvider {
    class ITypeMappingsProvider {
        virtual std::optional<std::reference_wrapper<ITypeMappings>> GetMappingsForGame(const std::string& Game) const = 0;

        virtual bool Reload() = 0;
    };
}