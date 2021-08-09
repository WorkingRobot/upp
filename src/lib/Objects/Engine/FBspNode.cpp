#include "FBspNode.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FBspNode& Value)
    {
		Ar >> Value.Plane;;
		Ar >> Value.iVertPool;
		Ar >> Value.iSurf;
		Ar >> Value.iVertexIndex;
		Ar >> Value.ComponentIndex;
		Ar >> Value.ComponentNodeIndex;
		Ar >> Value.ComponentElementIndex;

		Ar >> Value.iBack;
		Ar >> Value.iFront;
		Ar >> Value.Plane;
		Ar >> Value.iCollisionBound;
		Ar >> Value.iZone;
		Ar >> Value.NumVertices;
		Ar >> Value.NodeFlags;
		Ar >> Value.iLeaf;

        return Ar;
    }
}