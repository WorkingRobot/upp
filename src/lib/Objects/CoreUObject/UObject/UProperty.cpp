#include "UProperty.h"

namespace upp::Objects {
    UProperty::UProperty(FArchive& Ar, FSerializeCtx& Ctx, const Providers::Property& PropertyInfo, EReadType ReadType) :
        Tag(PropertyInfo),
        Data(Ar, Ctx, Tag, ReadType)
    {

    }

    UProperty::~UProperty()
    {
    }
}