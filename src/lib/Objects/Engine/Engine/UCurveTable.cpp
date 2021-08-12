#include "UCurveTable.h"

#include "../../../Vfs/Vfs.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/c97ef17630905fbf2373907cff8f83b4fa669ae9/Engine/Source/Runtime/Engine/Private/CurveTable.cpp#L97
    UCurveTable::UCurveTable(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO) :
        UObject(Ar, Schema, Ctx, IsCDO)
    {
        int NumRows;
        Ar >> NumRows;

        Ar >> CurveTableMode;

        auto& RowSchema = *Ctx.GetVfs().GetProvider()->GetSchema(CurveTableMode == ECurveTableMode::SimpleCurves ? "SimpleCurve" : "RichCurve");

        RowMap.reserve(NumRows);
        for (int Idx = 0; Idx < NumRows; ++Idx) {
            FName RowName;
            Ar >> RowName;

            RowMap.emplace_back(std::piecewise_construct, std::forward_as_tuple(RowName), std::forward_as_tuple(Ar, RowSchema, Ctx));
        }
    }
}