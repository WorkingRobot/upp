#include "FProperty.h"

namespace upp::Objects {
    FProperty::FProperty(FArchive& Ar, const Providers::Property& PropertyInfo, EReadType ReadType) :
        Tag(PropertyInfo),
        Data(Ar, Tag, ReadType)
    {

    }

    FProperty::~FProperty()
    {
    }
}