#include "USoundWave.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/65cbeac6d1bdefdf560f3f879db3f599cf166a3c/Engine/Source/Runtime/Engine/Private/SoundWave.cpp#L359
    USoundWave::USoundWave(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO) :
        USoundBase(Ar, Schema, Ctx, IsCDO)
    {
        int IsCooked;
        Ar >> IsCooked;

        constexpr bool SupportsStreaming = true;
        bool ShouldStreamSound = false;
        if (auto IsStreaming = Get<bool>("bStreaming")) {
            ShouldStreamSound = *IsStreaming;
        }
        /* UModel doesn't do anything else with this value, so I won't either
        * https://github.com/gildor2/UEViewer/blob/eaba2837228f9fe39134616d7bff734acd314ffb/Unreal/UnSound.h#L203
        * https://github.com/EpicGames/UnrealEngine/blob/65cbeac6d1bdefdf560f3f879db3f599cf166a3c/Engine/Source/Runtime/Engine/Private/SoundWave.cpp#L2292
        */

        if (IsCooked) {
            if (!ShouldStreamSound || !SupportsStreaming) {
                CompressedFormatData.Serialize(Ar, Ctx);
            }
        }
        else {
            RawData.Serialize(Ar, Ctx);
        }

        Ar >> CompressedDataGuid;

        if (ShouldStreamSound && IsCooked && SupportsStreaming) {
            // https://github.com/EpicGames/UnrealEngine/blob/4b4d7ca8be068c968dc9416b576c9d0d2f9d2f1f/Engine/Source/Runtime/Engine/Private/AudioDerivedData.cpp#L1465
            RunningPlatformData.Serialize(Ar, Ctx);
        }
    }
}