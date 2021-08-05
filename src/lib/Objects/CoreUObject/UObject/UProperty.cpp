#include "UProperty.h"

namespace upp::Objects {
    UProperty::UProperty(FArchive& Ar, const Providers::Property& PropertyInfo, EReadType ReadType) :
        Tag(PropertyInfo),
        Data(Ar, Tag, ReadType)
    {

    }

    UProperty::~UProperty()
    {
    }
}