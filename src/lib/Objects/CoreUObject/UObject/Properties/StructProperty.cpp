#pragma once

#include "../../../../Crc32.h"
#include "../../../../Providers/Schema.h"
#include "../../../Core/Math/FIntPoint.h"
#include "../../../Core/Math/FLinearColor.h"
#include "../../../Core/Math/FRotator.h"
#include "../../../Core/Math/FVector.h"
#include "../../../Core/Math/FVector2D.h"
#include "../../../Core/Misc/FFrameNumber.h"
#include "../../../Core/Misc/FGuid.h"
#include "../../../Engine/Curves/FRichCurveKey.h"
#include "../../../Engine/Curves/FSimpleCurveKey.h"
#include "../../../Engine/Engine/FSkeletalMeshSamplingLODBuiltData.h"
#include "../../../Engine/FMaterialInput.h"
#include "../../../Engine/TPerPlatformProperty.h"
#include "../../../GameplayTags/FGameplayTagContainer.h"
#include "../../../MovieScene/Channels/FMovieSceneFloatChannel.h"
#include "../../../MovieScene/Evaluation/FMovieSceneEvalTemplatePtr.h"
#include "../../../MovieScene/Evaluation/FMovieSceneEvaluationFieldEntityTree.h"
#include "../../../MovieScene/Evaluation/FMovieSceneEvaluationKey.h"
#include "../../../MovieScene/Evaluation/FMovieSceneTrackIdentifier.h"
#include "../../../MovieScene/Evaluation/FMovieSceneTrackImplementationPtr.h"
#include "../../../MovieScene/FMovieSceneFrameRange.h"
#include "../../../MovieScene/FMovieSceneSequenceID.h"
#include "../FSoftClassPath.h"
#include "../UObject.h"
#include "BaseProperty.h"

namespace upp::Objects {
    StructProperty::BaseProperty(FArchive& Ar, FSerializeCtx& Ctx, const UPropertyTag& Tag, EReadType ReadType)
    {
        auto& StructType = Tag.TagData.GetData().Struct.Schema->Name;
        switch (Crc32(StructType.GetString(), StructType.GetSize()))
        {
#define CASE(Name, Type) case Crc32(Name): { auto& Data = Value.emplace<Type>(); if (ReadType != EReadType::Zero) { Ar >> Data; } break; }
#define CASE_EX(Name, Type) case Crc32(Name): { auto& Data = Value.emplace<Type>(); if (ReadType != EReadType::Zero) { Data.Serialize(Ar, Ctx); } break; }

            CASE("ColorMaterialInput", FColorMaterialInput);
            CASE("FrameNumber", FFrameNumber);
            CASE("GameplayTagContainer", FGameplayTagContainer);
            CASE("Guid", FGuid);
            CASE("IntPoint", FIntPoint);
            CASE("LinearColor", FLinearColor);
            CASE_EX("MovieSceneEvalTemplatePtr", FMovieSceneEvalTemplatePtr);
            CASE("MovieSceneEvaluationFieldEntityTree", FMovieSceneEvaluationFieldEntityTree);
            CASE("MovieSceneEvaluationKey", FMovieSceneEvaluationKey);
            CASE("MovieSceneFloatChannel", FMovieSceneFloatChannel);
            CASE("MovieSceneFrameRange", FMovieSceneFrameRange);
            CASE("MovieSceneSequenceID", FMovieSceneSequenceID);
            CASE("MovieSceneTrackIdentifier", FMovieSceneTrackIdentifier);
            CASE_EX("MovieSceneTrackImplementationPtr", FMovieSceneTrackImplementationPtr);
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
            CASE("Vector2D", FVector2D);

#undef CASE
#ifdef _DEBUG
#define CASE(Name) case Crc32(Name): { printf("No parser written for " Name "!\n"); _CrtDbgBreak(); goto DefaultCase; }

            CASE("Box");
            CASE("Box2D");
            CASE("Color");
            CASE("DateTime");
            CASE("ExpressionInput");
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
            CASE("MovieSceneFloatValue");
            CASE("MovieSceneSegment");
            CASE("MovieSceneSegmentIdentifier");
            CASE("Plane");
            CASE("Quat");
            CASE("SectionEvaluationDataTree");
            CASE("Timespan");
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
                Value.emplace<UObject>(Ar, *Tag.TagData.GetData().Struct.Schema, Ctx);
            }
            else {
                Value.emplace<std::monostate>();
            }
            break;
        }
    }
}