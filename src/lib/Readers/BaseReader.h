#pragma once

#include "../IKeyChain.h"
#include "../Objects/Core/Serialization/FArchive.h"
#include "../Vfs/BaseVfs.h"
#include "Error.h"

namespace upp::Readers {
    class BaseReader {
    public:
        BaseReader(Objects::FArchive& Archive, const IKeyChain& KeyChain, uint32_t ReaderIdx = -1);

        virtual void Append(Vfs::BaseVfs& Vfs) = 0;

        bool HasError() const;

        Error GetError() const;

        uint32_t GetReaderIdx() const;

    protected:
        void SetError(Error NewError);

        static bool ValidateMountPoint(std::string& MountPoint);

        static void CompactFilePath(std::string& Path);

        Objects::FArchive& Ar;
        const IKeyChain& KeyChain;
        uint32_t ReaderIdx;

    private:
        Error StoredError;

        static uint32_t GenerateReaderIdx();
    };
}