#pragma once

#include "FPakInfo.h"

#include <filesystem>

namespace upp::UE4::Pak {
    class FileReader {
    public:
        FileReader(Readers::FArchive& Archive);

    private:
        void ReadIndex();

        void ReadIndexLegacy();

        Readers::FArchive& Ar;

        FPakInfo Info;
    };
}