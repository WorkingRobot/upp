#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "FFragment.h"

namespace upp::Objects {
    struct FUnversionedHeader {
        std::vector<bool> ZeroMask;
        std::vector<FFragment> Fragments;

        friend FArchive& operator>>(FArchive& Ar, FUnversionedHeader& Value);

    private:
        void LoadZeroMaskData(FArchive& Ar, uint32_t NumBits);
    };
}