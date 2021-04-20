#pragma once

#include "../Serialization/FArchive.h"

namespace upp::Objects {
    struct FIoStoreTocCompressedBlockEntry {
    public:
        uint64_t GetOffset() const {
            return *((uint64_t*)Data) & 0xFFFFFFFFFF;
        }

        uint32_t GetCompressedSize() const {
            return (*((uint32_t*)Data + 1) >> 8) & 0xFFFFFF;
        }

        uint32_t GetUncompressedSize() const {
            return *((uint32_t*)Data + 2) & 0xFFFFFF;
        }

        uint8_t GetCompressionMethodIndex() const {
            return *((uint32_t*)Data + 2) >> 24;
        }

        friend FArchive& operator>>(FArchive& Ar, FIoStoreTocCompressedBlockEntry& Value);

    private:
        char Data[5 + 3 + 3 + 1];
    };
}