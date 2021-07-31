#include "FPropertyTag.h"

namespace upp::Objects {
    FPropertyTag::FPropertyTag(const Providers::Property& PropertyInfo) :
        TagData(PropertyInfo.Data)
    {
        
    }

    FPropertyTag::FPropertyTag(const Providers::PropertyData& PropertyData) :
        TagData(PropertyData)
    {
    }
}