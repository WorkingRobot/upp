#include "FMeshToMeshVertData.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FMeshToMeshVertData& Value)
    {
        Ar >> Value.PositionBaryCoordsAndDist;
        Ar >> Value.NormalBaryCoordsAndDist;
        Ar >> Value.TangentBaryCoordsAndDist;
        Ar >> Value.SourceMeshVertIndices;
        Ar >> Value.Weight;
        Ar >> Value.Padding;

        return Ar;
    }
}