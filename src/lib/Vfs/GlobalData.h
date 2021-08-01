#pragma once

#include "../Objects/Core/Serialization/FArchive.h"
#include "../Objects/CoreUObject/Serialization/FScriptObjectEntry.h"

#include <unordered_map>

namespace upp::Vfs {
    class GlobalData {
    public:
        void Initialize(Objects::FArchive& NameAr, Objects::FArchive& HashAr, Objects::FArchive& MetaAr);

        static void ReadNameMap(Objects::FArchive& NameAr, uint32_t HashesSize, std::vector<std::string>& NameMap);

        const Objects::FScriptObjectEntry& GetEntry(const Objects::FPackageObjectIndex& Idx) const;

        const std::string& GetName(const Objects::FMappedName& Name) const;

    private:
        std::vector<std::string> NameMap;
        std::vector<Objects::FScriptObjectEntry> ScriptObjectEntries;
        std::unordered_map<Objects::FPackageObjectIndex, std::reference_wrapper<Objects::FScriptObjectEntry>> EntryLUT;
    };
}