#include "UTexture2D.h"

#include "../../Core/EPixelFormat.h"
#include "../FStripDataFlags.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/abee2073faa072b43e7ddb4dfe56299841cf9e42/Engine/Source/Runtime/Engine/Private/Texture2D.cpp#L180
    UTexture2D::UTexture2D(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO) :
        UTexture(Ar, Schema, Ctx, IsCDO)
    {
        FStripDataFlags StripDataFlags;
        Ar >> StripDataFlags;

        int IsCooked;
        Ar >> IsCooked;
        if (!IsCooked) {
            return;
        }

        // https://github.com/EpicGames/UnrealEngine/blob/abee2073faa072b43e7ddb4dfe56299841cf9e42/Engine/Source/Runtime/Engine/Private/TextureDerivedData.cpp#L2155
        while (true) {
            FName PixelFormatName;
            Ar >> PixelFormatName;
            if (PixelFormatName.IsNone()) {
                break;
            }

            int64_t SkipOffset;
            Ar >> SkipOffset;

            // https://github.com/EpicGames/UnrealEngine/blob/abee2073faa072b43e7ddb4dfe56299841cf9e42/Engine/Source/Runtime/RHI/Private/RHI.cpp#L1749
            // We're not using GPixelFormats here since we don't need to necessarily support the pixel format to read and store its data

            // https://github.com/EpicGames/UnrealEngine/blob/abee2073faa072b43e7ddb4dfe56299841cf9e42/Engine/Source/Runtime/Engine/Private/TextureDerivedData.cpp#L1581
            // https://github.com/EpicGames/UnrealEngine/blob/abee2073faa072b43e7ddb4dfe56299841cf9e42/Engine/Source/Runtime/Engine/Private/TextureDerivedData.cpp#L1382
            PlatformData.Serialize(Ar, Ctx);
        }
    }
}