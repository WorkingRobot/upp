#include "UDataTable.h"

#include "../../../Vfs/Vfs.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/1d9723e1f6ded1802b2a3faf650413887082e7fb/Engine/Source/Runtime/Engine/Private/DataTable.cpp#L225
    UDataTable::UDataTable(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO) :
        UObject(Ar, Schema, Ctx, IsCDO)
    {
        auto RowStruct = Get<FPackageIndex>("RowStruct");

        // https://github.com/EpicGames/UnrealEngine/blob/1d9723e1f6ded1802b2a3faf650413887082e7fb/Engine/Source/Runtime/Engine/Private/DataTable.cpp#L85
        int NumRows;
        Ar >> NumRows;

        if (!RowStruct) {
            return;
        }
        if (!RowStruct->IsImport()) {
            return;
        }
        auto& RowStructImport = Ctx.GetImport(RowStruct->GetValue());
        if (!RowStructImport.IsScriptImport()) {
            return;
        }
        auto& RowSchema = *Ctx.GetVfs().GetProvider()->GetSchema(Ctx.GetObjectName(RowStructImport));

        RowMap.reserve(NumRows);
        for (int Idx = 0; Idx < NumRows; ++Idx) {
            FName RowName;
            Ar >> RowName;

            RowMap.emplace_back(std::piecewise_construct, std::forward_as_tuple(RowName), std::forward_as_tuple(Ar, RowSchema, Ctx));
        }
    }
}