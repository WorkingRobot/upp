#include "GlobalData.h"

#include "../Objects/Core/UObject/FSerializedNameHeader.h"

namespace upp::Vfs {
    using namespace Objects;

    void GlobalData::Initialize(Objects::FArchive& NameAr, Objects::FArchive& HashAr, Objects::FArchive& MetaAr)
    {
        auto NameCount = HashAr.Size() / 8 - 1;
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

        MetaAr.ReadBuffer(ScriptObjectEntries);
    }
}