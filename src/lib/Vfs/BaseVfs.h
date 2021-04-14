#pragma once

#include "Directory.h"

namespace upp::Vfs {
    class BaseVfs {
        // global data

        // readers (adding and removing, etc)

        // append (for readers)
        virtual Directory<>& GetRootDirectory() = 0;
    };
}