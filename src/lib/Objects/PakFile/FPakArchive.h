#pragma once

#include "../../Readers/PakReader.h"
#include "FPakArchiveReader.h"

namespace upp::Objects {
    class FPakArchive : public FArchive {
    public:
        FPakArchive(const FPakEntry& Entry, Readers::PakReader& Reader);

        size_t Read(char* Data, size_t Size) override;

        size_t Size() const override;

        size_t Tell() const override;

        size_t Seek(ptrdiff_t Offset, ESeekDir Direction) override;

    private:
        std::unique_ptr<FPakArchiveReaderBase> Impl;

        size_t Position;
    };
}