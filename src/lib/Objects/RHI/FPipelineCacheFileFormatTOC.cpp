#include "FPipelineCacheFileFormatTOC.h"

namespace upp::Objects {
    constexpr uint64_t FileMagic = 0x544F435354415232; // TOCSTAR2 (reversed because of little endian)
    constexpr uint64_t FileMagicEOF = 0x454F462D4D41524B; // EOF-MARK (reversed because of little endian)

    FArchive& operator>>(FArchive& Ar, FPipelineCacheFileFormatTOC& Value)
    {
        uint64_t TOCMagic;
        Ar >> TOCMagic;
        if (TOCMagic != FileMagic) {
            return Ar;
        }

        uint64_t EOFMagic;
        Ar.PRead((char*)&EOFMagic, sizeof(FileMagicEOF), Ar.Size() - sizeof(FileMagicEOF));
        if (EOFMagic != FileMagicEOF) {
            return Ar;
        }

        bool AllEntriesUseSameGuid;
        Ar >> AllEntriesUseSameGuid;

        FGuid FirstEntryGuid;
        if (AllEntriesUseSameGuid) {
            Ar >> FirstEntryGuid;
        }

        Ar >> Value.SortedOrder;
        Ar >> Value.MetaData;

        if (AllEntriesUseSameGuid) {
            for (auto& [Key, Value] : Value.MetaData) {
                Value.FileGuid = FirstEntryGuid;
            }
        }

        return Ar;
    }
}