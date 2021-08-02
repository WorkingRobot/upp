#include "FTexturePlatformData.h"

namespace upp::Objects {
    constexpr uint32_t IsCubeMap = 1 << 31;
    constexpr uint32_t HasOptData = 1 << 30;

    void FTexturePlatformData::Serialize(FArchive& Ar, FSerializeCtx& Ctx)
    {
        Ar >> SizeX;
        Ar >> SizeY;
        Ar >> PackedData;
        std::string PixelFormatString;
        Ar >> PixelFormatString;
        PixelFormat = GetPixelFormat(PixelFormatString);

        if (PackedData & HasOptData) {
            // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/Engine/Classes/Engine/Texture.h#L426
            // Never used
        }

        // Unused when loading: https://github.com/EpicGames/UnrealEngine/blob/abee2073faa072b43e7ddb4dfe56299841cf9e42/Engine/Source/Runtime/Engine/Private/TextureDerivedData.cpp#L1451
        int FirstMipToSerialize;
        Ar >> FirstMipToSerialize;

        {
            int SerializeNum;
            Ar >> SerializeNum;
            Mips.reserve(SerializeNum);
            for (int i = 0; i < SerializeNum; ++i) {
                Mips.emplace_back().Serialize(Ar, Ctx);
            }
        }

        int IsVirtual;
        Ar >> IsVirtual;
        if (IsVirtual) {
            VTData.emplace().Serialize(Ar, Ctx);
        }
    }
}