#pragma once

#include "../../Objects/Core/Serialization/FArchive.h"
#include "ECompressionMethod.h"
#include "EVersion.h"

namespace upp::Providers::Usmap {
    struct Header {
        static constexpr uint16_t FileMagic = 0x30C4;

        uint16_t Magic;
        EVersion Version;
        ECompressionMethod Method;
        uint32_t CompSize;
        uint32_t DecompSize;

        friend Objects::FArchive& operator>>(Objects::FArchive& Ar, Header& Value);
    };
}