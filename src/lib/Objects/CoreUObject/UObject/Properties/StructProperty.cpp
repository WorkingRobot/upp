#pragma once

#include "../../../../Crc32.h"
#include "../../../../Providers/Schema.h"
#include "../../../Core/Math/FIntPoint.h"
#include "../../../Core/Math/FLinearColor.h"
#include "../../../Core/Math/FRotator.h"
#include "../../../Core/Math/FVector.h"
#include "../../../Core/Misc/FGuid.h"
#include "../../../Engine/Curves/FRichCurveKey.h"
#include "../../../Engine/Curves/FSimpleCurveKey.h"
#include "../../../Engine/Engine/FSkeletalMeshSamplingLODBuiltData.h"
#include "../../../Engine/TPerPlatformProperty.h"
#include "../../../GameplayTags/FGameplayTagContainer.h"
#include "../FSoftClassPath.h"
#include "../UObject.h"
#include "BaseProperty.h"

namespace upp::Objects {
    StructProperty::BaseProperty(FArchive& Ar, const UPropertyTag& Tag, EReadType ReadType)
    {
        auto& StructType = Tag.TagData.GetData().Struct.Schema->Name;
        switch (Crc32(StructType.GetString(), StructType.GetSize()))
        {
#define CASE(Name, Type) case Crc32(Name): { auto& Data = Value.emplace<Type>(); if (ReadType != EReadType::Zero) { Ar >> Data; } break; }

            CASE("GameplayTagContainer", FGameplayTagContainer);
            CASE("Guid", FGuid);
            CASE("IntPoint", FIntPoint);
            CASE("LinearColor", FLinearColor);
            CASE("PerPlatformBool", FPerPlatformBool);
            CASE("PerPlatformFloat", FPerPlatformFloat);
            CASE("PerPlatformInt", FPerPlatformInt);
            CASE("RichCurveKey", FRichCurveKey);
            CASE("Rotator", FRotator);
            CASE("SimpleCurveKey", FSimpleCurveKey);
            CASE("SkeletalMeshSamplingLODBuiltData", FSkeletalMeshSamplingLODBuiltData);
            CASE("SoftClassPath", FSoftClassPath);
            CASE("SoftObjectPath", FSoftObjectPath);
            CASE("Vector", FVector);

#undef CASE
#ifdef _DEBUG
#define CASE(Name) case Crc32(Name): { printf("No parser written for " Name "!\n"); _CrtDbgBreak(); goto DefaultCase; }

            CASE("Box");
            CASE("Box2D");
            CASE("Color");
            CASE("ColorMaterialInput");
            CASE("DateTime");
            CASE("ExpressionInput");
            CASE("FrameNumber");
            CASE("NavAgentSelector");
            CASE("SmartName");
            CASE("ScalarMaterialInput");
            CASE("ShadingModelMaterialInput");
            CASE("VectorMaterialInput");
            CASE("Vector2MaterialInput");
            CASE("MaterialAttributesInput");
            CASE("PerQualityLevelInt");
            CASE("IntVector");
            CASE("LevelSequenceObjectReferenceMap");
            CASE("NiagaraVariable");
            CASE("NiagaraVariableBase");
            CASE("NiagaraVariableWithOffset");
            CASE("MovieSceneEvalTemplatePtr");
            CASE("MovieSceneEvaluationFieldEntityTree");
            CASE("MovieSceneEvaluationKey");
            CASE("MovieSceneFloatChannel");
            CASE("MovieSceneFloatValue");
            CASE("MovieSceneFrameRange");
            CASE("MovieSceneSegment");
            CASE("MovieSceneSegmentIdentifier");
            CASE("MovieSceneSequenceID");
            CASE("MovieSceneTrackIdentifier");
            CASE("MovieSceneTrackImplementationPtr");
            CASE("Plane");
            CASE("Quat");
            CASE("SectionEvaluationDataTree");
            CASE("Timespan");
            CASE("Vector2D");
            CASE("Vector4");
            CASE("Vector_NetQuantize");
            CASE("Vector_NetQuantize10");
            CASE("Vector_NetQuantize100");
            CASE("Vector_NetQuantizeNormal");

        DefaultCase:
#undef CASE
#endif
        default:
            if (ReadType != EReadType::Zero) {
                Value.emplace<UObject>(Ar, *Tag.TagData.GetData().Struct.Schema);
            }
            else {
                Value.emplace<std::monostate>();
            }
            break;
        }
    }
}