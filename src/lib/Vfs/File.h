#pragma once

#include <stdint.h>

namespace upp::Vfs {
    class File {
    public:
        File() = default;

        File(uint32_t ReaderIdx, uint32_t FileIdx) :
            ReaderIdx(ReaderIdx),
            FileIdx(FileIdx)
        {

        }

        uint32_t GetReaderIdx() const noexcept {
            return ReaderIdx;
        }

        uint32_t GetFileIdx() const noexcept {
            return FileIdx;
        }

    private:
        uint32_t ReaderIdx;
        uint32_t FileIdx;
    };
}