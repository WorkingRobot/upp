#pragma once

#include "../Serialization/FArchive.h"
#include "EIoChunkType.h"

namespace upp::Objects {
    struct FIoChunkId {
        char Id[12];

        FIoChunkId() noexcept = default;

        FIoChunkId(uint64_t Id, uint16_t ChunkIndex, EIoChunkType IoChunkType) :
            Id{}
        {
            *(uint64_t*)(this->Id + 0) = Id;
            *(uint16_t*)(this->Id + 8) = ChunkIndex;
            *(uint8_t*)(this->Id + 11) = (uint8_t)IoChunkType;
        }

        friend FArchive& operator>>(FArchive& Ar, FIoChunkId& Value);

        uint64_t GetId() const {
            return *(uint64_t*)Id;
        }

        friend auto operator<=>(const FIoChunkId&, const FIoChunkId&) = default;
    };
}

namespace std {
    template<>
    struct hash<upp::Objects::FIoChunkId>
    {
        std::size_t operator()(upp::Objects::FIoChunkId const& s) const noexcept
        {
            return _Hash_array_representation(s.Id, sizeof(s.Id));
        }
    };
}