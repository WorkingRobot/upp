#pragma once

#include "FRawStaticIndexBuffer.h"

namespace upp::Objects {
    struct FAdditionalStaticMeshIndexBuffers {
		FRawStaticIndexBuffer ReversedIndexBuffer;
		FRawStaticIndexBuffer ReversedDepthOnlyIndexBuffer;
		FRawStaticIndexBuffer WireframeIndexBuffer;
		FRawStaticIndexBuffer AdjacencyIndexBuffer;
    };
}