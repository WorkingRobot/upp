#pragma once

#include "../IKeyChain.h"
#include "../Objects/Core/Serialization/FArchive.h"
#include "Error.h"

namespace upp::Vfs {
    class Vfs;
}

namespace upp::Readers {
    class BaseReader {
    public:
        BaseReader(Objects::FArchive& Archive, const IKeyChain& KeyChain, uint32_t ReaderIdx = -1);

        bool HasError() const;

        Error GetError() const;

        uint32_t GetReaderIdx() const;

        const Objects::FArchive& GetArchive() const;

        virtual std::unique_ptr<Objects::FArchive> OpenFile(uint32_t FileIdx) = 0;

        virtual void Append(Vfs::Vfs& Vfs) = 0;

    protected:
        void SetError(Error NewError);

        static bool ValidateMountPoint(std::string& MountPoint);

        static void CompactFilePath(std::string& Path);

        Objects::FArchive& Ar;
        const IKeyChain& KeyChain;

    private:
        Error StoredError;
        uint32_t ReaderIdx;
    };
}