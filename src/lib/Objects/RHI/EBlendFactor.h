#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class EBlendFactor : uint8_t {
        BF_Zero,
        BF_One,
        BF_SourceColor,
        BF_InverseSourceColor,
        BF_SourceAlpha,
        BF_InverseSourceAlpha,
        BF_DestAlpha,
        BF_InverseDestAlpha,
        BF_DestColor,
        BF_InverseDestColor,
        BF_ConstantBlendFactor,
        BF_InverseConstantBlendFactor,
        BF_Source1Color,
        BF_InverseSource1Color,
        BF_Source1Alpha,
        BF_InverseSource1Alpha,

        EBlendFactor_Num,
        EBlendFactor_NumBits = 4,
    };
    static_assert((uint8_t)EBlendFactor::EBlendFactor_Num <= (1 << (uint8_t)EBlendFactor::EBlendFactor_NumBits), "EBlendFactor_Num will not fit on EBlendFactor_NumBits");
}