#include "UModel.h"

#include "../FStripDataFlags.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/bccdec1d349b12e817b8d565884044ce6365a619/Engine/Source/Runtime/Engine/Private/Model.cpp#L186
    UModel::UModel(FArchive& Ar, const Providers::Schema& Schema, FSerializeCtx& Ctx, bool IsCDO) :
        UObject(Ar, Schema, Ctx, IsCDO)
    {
        FStripDataFlags StripFlags;
        Ar >> StripFlags;

        Ar >> Bounds;

        Ar.BulkSerialize(Vectors);
        Ar.BulkSerialize(Points);
        Ar.BulkSerialize(Nodes);

        for (auto& Node : Nodes) {
            Node.NodeFlags = EBspNodeFlags((uint8_t)Node.NodeFlags & ~((uint8_t)EBspNodeFlags::NF_IsNew | (uint8_t)EBspNodeFlags::NF_IsFront| (uint8_t)EBspNodeFlags::NF_IsBack));
        }

        Ar.ReadBuffer(Surfs);
        Ar.BulkSerialize(Verts);

        Ar >> NumSharedSides;

        int bRootOutside, bLinked;
        Ar >> bRootOutside >> bLinked;
        RootOutside = bRootOutside;
        Linked = bLinked;

        Ar >> NumUniqueVertices;

        constexpr int StripVertexBufferFlag = 1;
        if (!StripFlags.IsEditorDataStripped() || !StripFlags.IsClassDataStripped(StripVertexBufferFlag)) {
            Ar >> VertexBuffer;
        }

        Ar >> LightingGuid;
        Ar >> LightmassSettings;
    }
}