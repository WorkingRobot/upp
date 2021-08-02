#include "UObject.h"

#include "../../../Vfs/Vfs.h"
#include "../../Engine/Engine/UTexture2D.h"
#include "../Serialization/FIterator.h"

#include <numeric>

namespace upp::Objects {
    const Providers::Property* GetProperty(const Providers::Schema& Schema, uint16_t SchemaIdx)
    {
        auto Itr = std::find_if(Schema.Properties.begin(), Schema.Properties.end(), [SchemaIdx](const auto& Prop) {
            return Prop.SchemaIdx == SchemaIdx;
        });

        if (Itr != Schema.Properties.end()) {
            return &*Itr;
        }
        if (Schema.SuperType) {
            return GetProperty(*Schema.SuperType, SchemaIdx - Schema.PropCount);
        }
        return nullptr;
    }

    std::unique_ptr<UObject> UObject::SerializeUnversioned(FArchive& Ar, const std::string& ClassName, FSerializeCtx& Ctx, bool IsCDO)
    {
        auto& Provider = Ctx.GetVfs().GetProvider();
        if (!Provider) {
            return nullptr;
        }

        auto SchemaPtr = Provider->GetSchema(ClassName);
        if (!SchemaPtr) {
            return nullptr;
        }

        switch (Crc32(ClassName))
        {
#define CASE(Name, Type) case Crc32(Name): return std::make_unique<Type>(Ar, *SchemaPtr, Ctx, IsCDO)

        CASE("Texture2D", UTexture2D);

#undef CASE
        default: return std::unique_ptr<UObject>(new UObject(Ar, *SchemaPtr, IsCDO));
        }
    }

    UObject::UObject(FArchive& Ar, const Providers::Schema& Schema, bool IsCDO) :
        Schema(Schema)
    {
        FUnversionedHeader Header;
        Ar >> Header;

        Properties.reserve(std::accumulate(Header.Fragments.begin(), Header.Fragments.end(), 0u, [](uint32_t V, const FFragment& Frag) { return V + Frag.ValueNum; }));

        FIterator Itr(Header);
        if (Itr.IsValid()) {
            do {
                auto PropInfo = GetProperty(Schema, Itr.GetSchemaIdx());
                if (PropInfo) {
                    Properties.emplace_back(Ar, *PropInfo, Itr.IsNonZero() ? EReadType::Normal : EReadType::Zero);
                }
                // Could not get property info
                else {
                    if (Itr.IsNonZero()) {
                        return;
                    }
                    // It's okay though since it's zeroed and not really serialized
                }
            } while (++Itr);
        }

        if (!IsCDO) {
            int HasObjectGuid;
            Ar >> HasObjectGuid;
            if (HasObjectGuid) {
                FGuid Guid;
                Ar >> Guid;
            }
        }
    }
}