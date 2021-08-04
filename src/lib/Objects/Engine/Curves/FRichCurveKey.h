#pragma once

#include "../../Core/Serialization/FArchive.h"
#include "ERichCurveInterpMode.h"
#include "ERichCurveTangentMode.h"
#include "ERichCurveTangentWeightMode.h"

namespace upp::Objects {
    struct FRichCurveKey {
        ERichCurveInterpMode InterpMode;
        ERichCurveTangentMode TangentMode;
        ERichCurveTangentWeightMode TangentWeightMode;
        float Time;
        float Value;
        float ArriveTangent;
        float ArriveTangentWeight;
        float LeaveTangent;
        float LeaveTangentWeight;

        friend FArchive& operator>>(FArchive& Ar, FRichCurveKey& Value);
    };
}