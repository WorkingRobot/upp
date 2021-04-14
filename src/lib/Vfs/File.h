#pragma once

namespace upp::Vfs {
    class File {
    public:
        File(uint32_t ReaderIdx, uint32_t FileIdx) :
            ReaderIdx(ReaderIdx),
            FileIdx(FileIdx)
        {

        }

        uint32_t GetReaderIdx() const {
            return ReaderIdx;
        }

        uint32_t GetFileIdx() const {
            return FileIdx;
        }

    private:
        uint32_t ReaderIdx;
        uint32_t FileIdx;
    };
}