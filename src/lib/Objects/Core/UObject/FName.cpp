#include "FName.h"

namespace upp::Objects {
    FName::operator const std::string&() const
    {
        return *String;
    }

    bool FName::IsNone() const
    {
        return *String == "None";
    }
}