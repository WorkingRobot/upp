#include "FMultiSizeIndexContainer.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FMultiSizeIndexContainer& Value)
    {
        uint8_t DataTypeSize;
        Ar >> DataTypeSize;
        if (DataTypeSize == sizeof(uint16_t)) {
            Ar.BulkSerialize(Value.IndexStorage.emplace<std::vector<uint16_t>>());
        }
        else {
            Ar.BulkSerialize(Value.IndexStorage.emplace<std::vector<uint32_t>>());
        }

        return Ar;
    }
}