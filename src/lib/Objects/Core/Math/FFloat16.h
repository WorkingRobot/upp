#pragma once

#include "../Serialization/FArchive.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/d2acf8eff721d88a654648c6ac1c43137ae4dc23/Engine/Source/Runtime/Core/Public/Math/Float16.h#L27
    struct FFloat16 {
        union {
            struct {
                uint16_t Mantissa : 10;
                uint16_t Exponent : 5;
                uint16_t Sign : 1;
            };
            uint16_t Encoded;
        };
        
        constexpr FFloat16() :
            Encoded(0)
        {

        }

        constexpr FFloat16(float Val)
        {
            FFloat32 Float{ .Encoded = Val };

            Sign = Float.Sign;

            if (Float.Exponent <= 112) {
                Exponent = 0;
                Mantissa = 0;
                const int32_t NewExp = Float.Exponent - 127 + 15;

                if ((14 - NewExp) <= 24)
                {
                    uint32_t Mantissa = Float.Mantissa | 0x800000;
                    Mantissa = (uint16_t)(Mantissa >> (14 - NewExp));
                    if ((Mantissa >> (13 - NewExp)) & 1)
                    {
                        Encoded++;
                    }
                }
            }
            else if (Float.Exponent >= 143)
            {
                Exponent = 30;
                Mantissa = 1023;
            }
            else
            {
                Exponent = uint16_t(int32_t(Float.Exponent) - 127 + 15);
                Mantissa = uint16_t(Float.Mantissa >> 13);
            }
        }

        constexpr operator float() const noexcept
        {
            FFloat32 Result{ .Sign = Sign };

            if (Exponent == 0) {
                if (Mantissa == 0) {
                    Result.Exponent = 0;
                    Result.Mantissa = 0;
                }
                else {
                    uint32_t MantissaShift = 10 - (uint32_t)((int32_t)log2f((float)Mantissa));
                    Result.Exponent = 127 - (15 - 1) - MantissaShift;
                    Result.Mantissa = Mantissa << (MantissaShift + 23 - 10);
                }
            }
            else if (Exponent == 31) {
                Result.Exponent = 142;
                Result.Mantissa = 8380416;
            }
            else {
                Result.Exponent = int32_t(Exponent) - 15 + 127;
                Result.Mantissa = uint32_t(Mantissa) << 13;
            }

            return Result.Encoded;
        }

        friend FArchive& operator>>(FArchive& Ar, FFloat16& Value)
        {
            Ar >> Value.Encoded;

            return Ar;
        }

    private:
        union FFloat32 {
            struct {
                uint32_t Mantissa : 23;
                uint32_t Exponent : 8;
                uint32_t Sign : 1;
            };
            float Encoded;
        };
    };
}