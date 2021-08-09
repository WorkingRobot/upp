#pragma once

#include "../Core/Math/FPlane.h"
#include "../Core/Serialization/FArchive.h"
#include "../CoreUObject/UObject/FPackageIndex.h"
#include "EPolyFlags.h"

namespace upp::Objects {
    struct FBspSurf {
        FPackageIndex Material;
        EPolyFlags PolyFlags;
		int pBase;
		int vNormal;
		int vTextureU;
		int vTextureV;
		int iBrushPoly;
		FPackageIndex Actor;
		FPlane Plane;
		float LightMapScale;
		int iLightmassIndex;

        friend FArchive& operator>>(FArchive& Ar, FBspSurf& Value);
    };
}