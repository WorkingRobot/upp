#pragma once

#include "../Serialization/FArchive.h"

namespace upp::Objects {
    struct FIoOffsetAndLength {
    public:
        uint64_t GetOffset() const {
            return uint64_t(OffsetAndLength[4])
                | (uint64_t(OffsetAndLength[3]) << 8)
                | (uint64_t(OffsetAndLength[2]) << 16)
                | (uint64_t(OffsetAndLength[1]) << 24)
                | (uint64_t(OffsetAndLength[0]) << 32);
        }

        uint64_t GetLength() const {
            return uint64_t(OffsetAndLength[9])
                | (uint64_t(OffsetAndLength[8]) << 8)
                | (uint64_t(OffsetAndLength[7]) << 16)
                | (uint64_t(OffsetAndLength[6]) << 24)
                | (uint64_t(OffsetAndLength[5]) << 32);
        }

        friend FArchive& operator>>(FArchive& Ar, FIoOffsetAndLength& Value);

    private:
        uint8_t OffsetAndLength[5 + 5];
    };
}