#include "FArchive.h"

namespace upp::Objects {
    const std::string& FArchive::GetName() const
    {
        return Name;
    }

    FArchive::FArchive(const std::string& Name) :
        Name(Name)
    {

    }
}