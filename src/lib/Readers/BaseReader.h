#pragma once

#include "../IKeyChain.h"
#include "../Objects/Core/IO/FIoChunkId.h"
#include "../Objects/Core/Serialization/FArchive.h"
#include "../Objects/CoreUObject/UObject/UPackage.h"
#include "../Vfs/Directory.h"
#include "Error.h"

namespace upp::Vfs {
    class Vfs;
}

namespace upp::Readers {
    class BaseReader {
    public:
        BaseReader(Objects::FArchive& Archive, const IKeyChain& KeyChain, uint32_t ReaderIdx = -1);

        virtual ~BaseReader() = default;

        bool HasError() const;

        Error GetError() const;

        uint32_t GetReaderIdx() const;

        const Objects::FArchive& GetArchive() const;

        virtual uint32_t FindChunk(const Objects::FIoChunkId& Id) const;

        virtual std::unique_ptr<Objects::FArchive> OpenFile(uint32_t FileIdx) = 0;

        virtual std::unique_ptr<Objects::UPackage> ExportPackage(uint32_t AssetIdx, Vfs::Vfs& Vfs) = 0;

        virtual void Append(Vfs::Vfs& Vfs, bool TranslatePaths = false) = 0;

    protected:
        void SetError(Error NewError);

        static bool ValidateMountPoint(std::string& MountPoint);

        // Compacts file paths, given that Directory is a root directory
        static void MergeDirectory(Vfs::Vfs& Vfs, bool TranslatePaths, Vfs::Directory<>&& Directory);

        Objects::FArchive& Ar;
        const IKeyChain& KeyChain;

    private:
        Error StoredError;
        uint32_t ReaderIdx;
    };
}