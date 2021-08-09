#pragma once

#include "FArchive.h"

namespace upp::Objects {
    class FBufferArchive : public FArchive {
    public:
        FBufferArchive(const char* Data, size_t DataSize, const std::string& Name);

        size_t Read(char* Data, size_t Size) override;

        size_t Size() const override;

        size_t Tell() const override;

        size_t Seek(ptrdiff_t Offset, ESeekDir Direction) override;

        size_t PRead(char* Data, size_t Size, size_t Offset) override;

    private:
        const char* Data;
        size_t DataSize;
        size_t Position;
    };
}