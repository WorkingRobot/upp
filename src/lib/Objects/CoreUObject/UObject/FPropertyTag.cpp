#include "FPropertyTag.h"

namespace upp::Objects {
    FPropertyTag::FPropertyTag(const Providers::Property& PropertyInfo) :
        Name(PropertyInfo.Name),
        TagData(PropertyInfo.Data)
    {
        
    }

    FPropertyTag::FPropertyTag(const Providers::PropertyData& PropertyData) :
        Name("Unnamed"),
        TagData(PropertyData)
    {
    }
}