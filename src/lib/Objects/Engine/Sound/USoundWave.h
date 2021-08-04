#pragma once

#include "../../CoreUObject/Serialization/FByteBulkData.h"
#include "../../CoreUObject/Serialization/FFormatContainer.h"
#include "FStreamedAudioPlatformData.h"
#include "USoundBase.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/65cbeac6d1bdefdf560f3f879db3f599cf166a3c/Engine/Source/Runtime/Engine/Classes/Sound/SoundWave.h#L287
    struct USoundWave : public USoundBase {
        FFormatContainer CompressedFormatData;
        FByteBulkData RawData;
        FGuid CompressedDataGuid;
        FStreamedAudioPlatformData RunningPlatformData;

        USoundWave(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO);
    };
}