#pragma once

#include "FAESKey.h"

#include <wmmintrin.h>

namespace upp::Objects {
    class FAESSchedule {
    public:
        FAESSchedule(const FAESKey& Key);

        __forceinline void Decrypt(const char Input[16], char Output[16]) const
        {
            __m128i m = _mm_loadu_si128((__m128i*)Input);

            m = _mm_xor_si128(m, Steps[0]);
            m = _mm_aesdec_si128(m, Steps[1]);
            m = _mm_aesdec_si128(m, Steps[2]);
            m = _mm_aesdec_si128(m, Steps[3]);
            m = _mm_aesdec_si128(m, Steps[4]);
            m = _mm_aesdec_si128(m, Steps[5]);
            m = _mm_aesdec_si128(m, Steps[6]);
            m = _mm_aesdec_si128(m, Steps[7]);
            m = _mm_aesdec_si128(m, Steps[8]);
            m = _mm_aesdec_si128(m, Steps[9]);
            m = _mm_aesdec_si128(m, Steps[10]);
            m = _mm_aesdec_si128(m, Steps[11]);
            m = _mm_aesdec_si128(m, Steps[12]);
            m = _mm_aesdec_si128(m, Steps[13]);

            m = _mm_aesdeclast_si128(m, Key);

            _mm_storeu_si128((__m128i*)Output, m);
        }

        __forceinline void DecryptInPlace(char* Buffer, size_t BufferSize) const
        {
            for (; BufferSize >= 16; BufferSize -= 16, Buffer += 16) {
                Decrypt(Buffer, Buffer);
            }

            if (BufferSize) {
                char Data[16]{};
                memcpy(Data, Buffer, BufferSize);
                Decrypt(Data, Data);
                memcpy(Buffer, Data, BufferSize);
            }
        }

    private:
        __m128i Key;
        __m128i Steps[14];
    };
}