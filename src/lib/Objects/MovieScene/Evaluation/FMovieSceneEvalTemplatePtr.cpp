#include "FMovieSceneEvalTemplatePtr.h"

#include "../../../Vfs/Vfs.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/MovieScene/Private/Evaluation/MovieSceneEvalTemplateSerializer.h#L20
    // The Serialize method redirects here since FMovieSceneEvalTemplatePtr is a TInlineValue
    void FMovieSceneEvalTemplatePtr::Serialize(FArchive& Ar, FSerializeCtx& Ctx)
    {
        std::string TypeName;
        Ar >> TypeName;

        if (TypeName.empty()) {
            return;
        }

        // /Script/UMG.MovieSceneWidgetMaterialSectionTemplate
        auto DotOffset = TypeName.rfind('.');
#ifdef _DEBUG
        if (DotOffset == std::string::npos) {
            _CrtDbgBreak();
        }
#endif
        auto& TypeSchema = *Ctx.GetVfs().GetProvider()->GetSchema(TypeName.substr(DotOffset + 1));
        Data.emplace(Ar, TypeSchema, Ctx);
    }
}