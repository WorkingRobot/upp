#include "FAESSchedule.h"

namespace upp::Objects {
    __forceinline __m128i aes128_keyexpand(__m128i Key)
    {
        Key = _mm_xor_si128(Key, _mm_slli_si128(Key, 4));
        Key = _mm_xor_si128(Key, _mm_slli_si128(Key, 4));
        return _mm_xor_si128(Key, _mm_slli_si128(Key, 4));
    }

    FAESSchedule::FAESSchedule(const FAESKey& Key)
    {
        __m128i EncStep1 = _mm_loadu_si128((const __m128i*) Key.Key);
        __m128i EncStep2 = _mm_loadu_si128((const __m128i*) (Key.Key + 16));

#define KEYEXP128_H(K1, K2, I, S) _mm_xor_si128(aes128_keyexpand(K1), _mm_shuffle_epi32(_mm_aeskeygenassist_si128(K2, I), S))
#define KEYEXP256(K1, K2, I) KEYEXP128_H(K1, K2, I, 0xFF)
#define KEYEXP256_2(K1, K2)  KEYEXP128_H(K1, K2, 0x00, 0xAA)

#define RUN_STEP(I, TopInd) \
        EncStep1 = KEYEXP256(EncStep1, EncStep2, I);	\
        EncStep2 = KEYEXP256_2(EncStep2, EncStep1);		\
        Steps[TopInd] = _mm_aesimc_si128(EncStep1);		\
        Steps[TopInd - 1] = _mm_aesimc_si128(EncStep2);

        this->Key = EncStep1;
        Steps[13] = _mm_aesimc_si128(EncStep2);
        RUN_STEP(0x01, 12);
        RUN_STEP(0x02, 10);
        RUN_STEP(0x04, 8);
        RUN_STEP(0x08, 6);
        RUN_STEP(0x10, 4);
        RUN_STEP(0x20, 2);
        Steps[0] = KEYEXP256(EncStep1, EncStep2, 0x40);

#undef RUN_STEP
#undef KEYEXP256
#undef KEYEXP256_2
#undef KEYEXP128_H
    }
}