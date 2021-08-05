#include "UPropertyData.h"

namespace upp::Objects {
    decltype(UPropertyData::Data) UPropertyData::Construct(FArchive& Ar, const UPropertyTag& Tag, EReadType ReadType)
    {
        switch (Tag.TagData.GetType())
        {
#define CASE(Var) case Providers::EPropertyType::##Var##Property: return Var##Property(Ar, Tag, ReadType); break

            CASE(Byte);
            CASE(Bool);
            CASE(Int);
            CASE(Float);
            CASE(Object);
            CASE(Name);
            CASE(Delegate);
            CASE(Double);
            CASE(Array);
            CASE(Struct);
            CASE(Str);
            CASE(Text);
            CASE(Interface);
            CASE(MulticastDelegate);
            CASE(WeakObject);
            CASE(LazyObject);
            CASE(AssetObject);
            CASE(SoftObject);
            CASE(UInt64);
            CASE(UInt32);
            CASE(UInt16);
            CASE(Int64);
            CASE(Int16);
            CASE(Int8);
            CASE(Map);
            CASE(Set);
            CASE(Enum);
            CASE(FieldPath);

#undef CASE
        }
    }
}