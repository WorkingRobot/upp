#include "FByteBulkData.h"

namespace upp::Objects {
    void FByteBulkData::Serialize(FArchive& Ar, FSerializeCtx& Ctx)
    {
        Ar >> BulkDataFlags;

        int64_t BulkDataSizeOnDisk;

        // FModel doesn't even support 64bit
        if ((uint32_t)BulkDataFlags & (uint32_t)EBulkDataFlags::BULKDATA_Size64Bit) [[unlikely]] {
            Ar >> BulkDataSize;
            Ar >> BulkDataSizeOnDisk;
        }
        else {
            int32_t Val;

            Ar >> Val;
            BulkDataSize = Val;

            Ar >> Val;
            BulkDataSizeOnDisk = Val;
        }

        Ar >> BulkDataOffset;

        if ((uint32_t)BulkDataFlags & (uint32_t)EBulkDataFlags::BULKDATA_BadDataVersion) [[unlikely]] {
            uint16_t Val;
            Ar >> Val;
        }

        if ((uint32_t)BulkDataFlags & (uint32_t)EBulkDataFlags::BULKDATA_Unused) {
            return;
        }

        if ((uint32_t)BulkDataFlags & (uint32_t)EBulkDataFlags::BULKDATA_SerializeCompressedZLIB) {
            // https://github.com/EpicGames/UnrealEngine/blob/abee2073faa072b43e7ddb4dfe56299841cf9e42/Engine/Source/Runtime/Core/Private/Serialization/Archive.cpp#L685
            // never actually used
            return;
        }

        if ((uint32_t)BulkDataFlags & (uint32_t)EBulkDataFlags::BULKDATA_ForceInlinePayload) {
            Data = std::make_unique<char[]>(BulkDataSize);
            Ar.Read(Data.get(), BulkDataSize);
        }
        else if ((uint32_t)BulkDataFlags & (uint32_t)EBulkDataFlags::BULKDATA_OptionalPayload) {
            auto DataArPtr = Ctx.GetSiblingArchive("uptnl");
            if (DataArPtr) {
                Data = std::make_unique<char[]>(BulkDataSize);
                DataArPtr->PRead(Data.get(), BulkDataSize, BulkDataOffset);
            }
        }
        else if ((uint32_t)BulkDataFlags & (uint32_t)EBulkDataFlags::BULKDATA_PayloadInSeperateFile) {
            auto DataArPtr = Ctx.GetSiblingArchive("ubulk");
            if (DataArPtr) {
                Data = std::make_unique<char[]>(BulkDataSize);
                DataArPtr->PRead(Data.get(), BulkDataSize, BulkDataOffset);
            }
        }
        // only used in uexp files, so this is never actually called
        else if ((uint32_t)BulkDataFlags & (uint32_t)EBulkDataFlags::BULKDATA_PayloadAtEndOfFile) {
            Data = std::make_unique<char[]>(BulkDataSize);
            Ar.PRead(Data.get(), BulkDataSize, BulkDataOffset);
        }
    }
}