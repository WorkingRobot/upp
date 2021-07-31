#include "FUnversionedHeader.h"

#include "../../../Align.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/024cd72839c4eb94a5c20a0bf1dcb1a5c2868804/Engine/Source/Runtime/CoreUObject/Private/Serialization/UnversionedPropertySerialization.cpp#L431
    FArchive& operator>>(FArchive& Ar, FUnversionedHeader& Value)
    {
        uint32_t ZeroMaskNum = 0;
        uint32_t UnmaskedNum = 0;
        do {
            auto& Fragment = Value.Fragments.emplace_back();
            Ar >> Fragment;

            (Fragment.HasAnyZeroes ? ZeroMaskNum : UnmaskedNum) += Fragment.ValueNum;

            if (Fragment.IsLast) {
                break;
            }
        } while (true);

        if (ZeroMaskNum) {
            Value.LoadZeroMaskData(Ar, ZeroMaskNum);
        }

        return Ar;
    }

    void FUnversionedHeader::LoadZeroMaskData(FArchive& Ar, uint32_t NumBits)
    {
        // MSVC STL specific, not tested on others
        if (NumBits <= 8) {
            ZeroMask.resize(8);
            Ar >> *(uint8_t*)ZeroMask._Myvec.data();
        }
        else if (NumBits <= 16) {
            ZeroMask.resize(16);
            Ar >> *(uint16_t*)ZeroMask._Myvec.data();
        }
        else {
            ZeroMask.resize(Align<32>(NumBits));
            auto Data = (uint32_t*)ZeroMask._Myvec.data();
            int32_t BitsToRead = NumBits;
            do {
                Ar >> *(Data++);
                BitsToRead -= 32;
            } while (BitsToRead > 0);
        }
        ZeroMask.resize(NumBits);
        ZeroMask.shrink_to_fit();
    }
}