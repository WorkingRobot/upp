#pragma once

#include "FSoftObjectPath.h"

namespace upp::Objects {
    // It inherits from FSoftObjectPath but has no extra fields or serialization code
    using FSoftClassPath = FSoftObjectPath;
}