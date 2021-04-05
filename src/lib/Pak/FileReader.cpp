#include "FileReader.h"

namespace upp::UE4::Pak {
    FileReader::FileReader(Readers::FArchive& Archive) :
        Ar(Archive)
    {
        if (Ar.HasError()) {
            return;
        }

        // TODO: try more versions
        Ar.Seek(-FPakInfo::GetSerializedSize(), Readers::SeekDir::End);
        Ar >> Info;
        if (Ar.HasError()) {
            return;
        }
        if (Info.Version > EPakVersion::Latest) {
            // Version is newer than supported, continuing
        }

        if (Info.Version >= EPakVersion::PathHashIndex) {
            ReadIndex();
        }
        else {
            ReadIndexLegacy();
        }
    }

    void FileReader::ReadIndexLegacy()
    {
        if (Ar.HasError()) {
            return;
        }


    }
}