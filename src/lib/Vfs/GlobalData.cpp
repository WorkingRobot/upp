#include "GlobalData.h"

#include "../Objects/Core/UObject/FSerializedNameHeader.h"

namespace upp::Vfs {
    using namespace Objects;

    void GlobalData::Initialize(FArchive& NameAr, FArchive& HashAr, FArchive& MetaAr)
    {
        GlobalData::ReadNameMap(NameAr, HashAr.Size(), NameMap);

        MetaAr.ReadBuffer(ScriptObjectEntries);

        for (auto& Entry : ScriptObjectEntries) {
            EntryLUT.emplace(Entry.GlobalIndex, Entry);
        }
    }

    void GlobalData::ReadNameMap(FArchive& NameAr, uint32_t HashesSize, std::vector<std::string>& NameMap)
    {
        auto NameCount = HashesSize / 8 - 1;
        NameMap.resize(NameCount);
        for (auto& Name : NameMap) {
            FSerializedNameHeader Header;
            NameAr >> Header;
            if (Header.IsUtf16) [[unlikely]] {
                std::wstring StringData(Header.Len, '\0');
                NameAr.Read((char*)StringData.data(), Header.Len * sizeof(char16_t));
                Name = std::filesystem::path(StringData).string();
            }
            else {
                Name.resize(Header.Len);
                NameAr.Read(Name.data(), Header.Len);
            }
        }
    }

    const FScriptObjectEntry& GlobalData::GetEntry(const FPackageObjectIndex& Idx) const
    {
        return EntryLUT.at(Idx);
    }

    const std::string& GlobalData::GetName(const FMappedName& Name) const
    {
        return NameMap[Name.GetIndex()];
    }
}