#pragma once

#include "../UE4/Versions/EGame.h"
#include "../MappingsProvider/ITypeMappingsProvider.h"

namespace upp::FileProvider {
    class IFileProvider {
        virtual UE4::Versions::EGame GetGame() = 0;

        virtual const ITypeMappingsProvider& GetMappingsContainer() = 0;
    };
}