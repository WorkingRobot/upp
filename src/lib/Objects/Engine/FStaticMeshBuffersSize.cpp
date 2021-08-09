#include "FStaticMeshBuffersSize.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FStaticMeshBuffersSize& Value)
    {
		Ar >> Value.SerializedBuffersSize;
		Ar >> Value.DepthOnlyIBSize;
		Ar >> Value.ReversedIBsSize;

		return Ar;
	}
}