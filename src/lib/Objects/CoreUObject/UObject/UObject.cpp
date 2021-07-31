#include "UObject.h"

#include "../../../Vfs/Vfs.h"
#include "../Serialization/FIterator.h"

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

    std::unique_ptr<UObject> UObject::SerializeUnversioned(FArchive& Ar, const std::string& ClassName, Vfs::Vfs& Vfs)
    {
        auto& Provider = Vfs.GetProvider();
        if (!Provider) {
            return nullptr;
        }

        auto SchemaPtr = Provider->GetSchema(ClassName);
        if (!SchemaPtr) {
            return nullptr;
        }

        return std::unique_ptr<UObject>(new UObject(Ar, *SchemaPtr));
    }

    UObject::UObject(FArchive& Ar, const Providers::Schema& Schema)
    {
        FUnversionedHeader Header;
        Ar >> Header;

        FIterator Itr(Header);
        if (Itr.IsValid()) {
            do {
                if (!Itr.ShouldSerialize()) {
                    continue;
                }

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
    }
}