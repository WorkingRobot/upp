#pragma once

#include "FArchive.h"

#include <memory>

namespace upp::Objects {
    class FByteArchive : public FArchive {
    public:
        FByteArchive(std::unique_ptr<char[]>&& Data, size_t DataSize, const std::string& Name);

        size_t Read(char* Data, size_t Size) override;

        size_t Size() const override;

        size_t Tell() const override;

        size_t Seek(ptrdiff_t Offset, ESeekDir Direction) override;

    private:
        std::unique_ptr<char[]> Data;
        size_t DataSize;
        size_t Position;
    };
}