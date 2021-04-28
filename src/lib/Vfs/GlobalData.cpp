#include "GlobalData.h"

#include "../Objects/Core/UObject/FSerializedNameHeader.h"

namespace upp::Vfs {
    using namespace Objects;

    void GlobalData::Initialize(FArchive& NameAr, FArchive& HashAr, FArchive& MetaAr)
    {
        GlobalData::ReadNameMap(NameAr, HashAr.Size(), NameMap);

        MetaAr.ReadBuffer(ScriptObjectEntries);
    }

    void GlobalData::ReadNameMap(FArchive& NameAr, uint32_t HashesSize, std::vector<std::string>& NameMap)
    {
        auto NameCount = HashesSize / 8 - 1;
        NameMap.resize(NameCount);
        for (auto& Name : NameMap) {
            FSerializedNameHeader Header;
            NameAr >> Header;
            if (Header.IsUtf16()) {
                auto StringData = std::make_unique<char16_t[]>(Header.Len());
                NameAr.Read((char*)StringData.get(), Header.Len() * sizeof(char16_t));
                Name = { StringData.get(), StringData.get() + Header.Len() };
            }
            else {
                Name.resize(Header.Len());
                NameAr.Read(Name.data(), Header.Len());
            }
        }
    }

    const FScriptObjectEntry& GlobalData::GetEntry(const FPackageObjectIndex& Idx) const
    {
        return *std::find_if(ScriptObjectEntries.begin(), ScriptObjectEntries.end(), [&](const FScriptObjectEntry& Entry) {
            return Entry.GlobalIndex == Idx;
        });
    }

    const std::string& GlobalData::GetName(const FMappedName& Name) const
    {
        if (Name.GetType() != EMappedNameType::Global) {
            printf("oops\n");
        }
        return NameMap[Name.GetIndex()];
    }
}