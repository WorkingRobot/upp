#pragma once

#include "../Core/Math/FPlane.h"
#include "../Core/Serialization/FArchive.h"
#include "EBspNodeFlags.h"

namespace upp::Objects {
    struct FBspNode {
        FPlane Plane;
        int iVertPool;
        int iSurf;
        int iVertexIndex;
        uint16_t ComponentIndex;
        uint16_t ComponentNodeIndex;
        int ComponentElementIndex;

        int iBack;
        int iFront;
        int iPlane;
        int iCollisionBound;
        uint8_t iZone[2];
        uint8_t NumVertices;
        EBspNodeFlags NodeFlags;
        int iLeaf[2];

        friend FArchive& operator>>(FArchive& Ar, FBspNode& Value);
    };
}