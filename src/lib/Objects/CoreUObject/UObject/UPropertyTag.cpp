#include "UPropertyTag.h"

namespace upp::Objects {
    UPropertyTag::UPropertyTag(const Providers::Property& PropertyInfo) :
        TagData(PropertyInfo.Data)
    {
        
    }

    UPropertyTag::UPropertyTag(const Providers::PropertyData& PropertyData) :
        TagData(PropertyData)
    {

    }
}