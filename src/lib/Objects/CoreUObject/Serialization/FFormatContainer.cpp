#include "FFormatContainer.h"

namespace upp::Objects {
    void FFormatContainer::Serialize(FArchive& Ar, FSerializeCtx& Ctx)
    {
        int NumFormats;
        Ar >> NumFormats;

        Formats.reserve(NumFormats);
        for (int Idx = 0; Idx < NumFormats; ++Idx) {
            FName Name;
            Ar >> Name;
            auto& BulkData = Formats.emplace_back(std::piecewise_construct, std::forward_as_tuple(std::move(Name)), std::forward_as_tuple()).second;
            BulkData.Serialize(Ar, Ctx);
        }
    }
}