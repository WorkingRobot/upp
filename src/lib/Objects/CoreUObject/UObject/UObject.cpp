#include "UObject.h"

#include "../../../Vfs/Vfs.h"
#include "../../Engine/Engine/UBlueprintGeneratedClass.h"
#include "../../Engine/Engine/UCurveTable.h"
#include "../../Engine/Engine/UDataTable.h"
#include "../../Engine/Engine/ULevel.h"
#include "../../Engine/Engine/UModel.h"
#include "../../Engine/Engine/UStaticMesh.h"
#include "../../Engine/Engine/UTexture2D.h"
#include "../../Engine/Engine/UTextureCube.h"
#include "../../Engine/Engine/UVolumeTexture.h"
#include "../../Engine/Engine/UWorld.h"
#include "../../Engine/PhysicsEngine/UBodySetup.h"
#include "../../Engine/Sound/USoundWave.h"
#include "../../UMG/Blueprint/UWidgetBlueprintGeneratedClass.h"
#include "../Serialization/FIterator.h"
#include "UFunction.h"

#include <numeric>

namespace upp::Objects {
    const Providers::Property* GetSchemaProperty(const Providers::Schema& Schema, uint16_t SchemaIdx)
    {
        auto Itr = std::find_if(Schema.Properties.begin(), Schema.Properties.end(), [SchemaIdx](const auto& Prop) {
            return Prop.SchemaIdx == SchemaIdx;
        });

        if (Itr != Schema.Properties.end()) {
            return &*Itr;
        }
        if (Schema.SuperType) {
            return GetSchemaProperty(*Schema.SuperType, SchemaIdx - Schema.PropCount);
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

            CASE("BlueprintGeneratedClass", UBlueprintGeneratedClass);
            CASE("BodySetup", UBodySetup);
            CASE("CurveTable", UCurveTable);
            CASE("DataTable", UDataTable);
            CASE("Function", UFunction);
            CASE("Level", ULevel);
            CASE("Model", UModel);
            CASE("SoundWave", USoundWave);
            CASE("StaticMesh", UStaticMesh);
            CASE("Texture2D", UTexture2D);
            CASE("TextureCube", UTextureCube);
            CASE("VolumeTexture", UVolumeTexture);
            CASE("WidgetBlueprintGeneratedClass", UWidgetBlueprintGeneratedClass);
            CASE("World", UWorld);

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
                auto PropInfo = GetSchemaProperty(Schema, Itr.GetSchemaIdx());
                if (PropInfo) {
                    Properties.emplace_back(std::piecewise_construct, std::forward_as_tuple(Itr.GetSchemaIdx()), std::forward_as_tuple(Ar, *PropInfo, Itr.IsNonZero() ? EReadType::Normal : EReadType::Zero));
                }
                // Could not get property info
                else {
#ifdef _DEBUG
                    _CrtDbgBreak();
#endif
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

    const UProperty* UObject::GetProperty(uint32_t SchemaIdx) const
    {
        auto Itr = std::find_if(Properties.begin(), Properties.end(), [SchemaIdx](const auto& Prop) {
            return Prop.first == SchemaIdx;
        });
        return Itr != Properties.end() ? &Itr->second : nullptr;
    }

    uint32_t GetSchemaIdx(const Providers::Schema& Schema, const std::string& Name)
    {
        auto Itr = std::find_if(Schema.Properties.begin(), Schema.Properties.end(), [&Name](const auto& Prop) {
            return Prop.Name == Name;
        });
        if (Itr != Schema.Properties.end()) {
            return Itr->SchemaIdx;
        }
        if (Schema.SuperType) {
            return Schema.PropCount + GetSchemaIdx(*Schema.SuperType, Name);
        }
        return -1;
    }

    const UProperty* UObject::GetProperty(const std::string& Name) const
    {
        auto SchemaIdx = GetSchemaIdx(Schema, Name);
        return SchemaIdx != -1 ? GetProperty(SchemaIdx) : nullptr;
    }
}