#pragma once

#include "../Objects/Core/Serialization/FArchive.h"
#include "../Objects/CoreUObject/Serialization/FScriptObjectEntry.h"

namespace upp::Vfs {
    class GlobalData {
    public:
        void Initialize(Objects::FArchive& NameAr, Objects::FArchive& HashAr, Objects::FArchive& MetaAr);

    private:
        std::vector<std::string> NameMap;
        std::vector<Objects::FScriptObjectEntry> ScriptObjectEntries;
    };
}