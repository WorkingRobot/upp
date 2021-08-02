#pragma once

#include "../Core/Serialization/FArchive.h"
#include "EStrippedData.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/abee2073faa072b43e7ddb4dfe56299841cf9e42/Engine/Source/Runtime/Engine/Public/EngineUtils.h#L809
    struct FStripDataFlags {
        uint8_t GlobalStripFlags;
        uint8_t ClassStripFlags;

        bool IsEditorDataStripped() const {
            return (GlobalStripFlags & (uint8_t)EStrippedData::Editor) != 0;
        }

        bool IsDataStrippedForServer() const {
            return (GlobalStripFlags & (uint8_t)EStrippedData::Server) != 0;
        }

        bool IsClassDataStripped(uint8_t InFlags) const {
            return (ClassStripFlags & InFlags) != 0;
        }

        friend FArchive& operator>>(FArchive& Ar, FStripDataFlags& Value);
    };
}