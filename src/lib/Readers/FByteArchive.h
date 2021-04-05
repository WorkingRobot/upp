#pragma once

#include "FArchive.h"

#include <memory>

namespace upp::Readers {
    class FByteArchive : public FArchive {
    public:
        FByteArchive(std::unique_ptr<char[]>&& Data, size_t DataSize, Versions::EGame Game, const std::string& Name);

        size_t Read(char* Data, size_t Size) override;

        size_t Size() const override;

        size_t Tell() const override;

        size_t Seek(ptrdiff_t Offset, SeekDir Direction) override;

    private:
        std::unique_ptr<char[]> Data;
        size_t DataSize;
        size_t Position;
    };
}