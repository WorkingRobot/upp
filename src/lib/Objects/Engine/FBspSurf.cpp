#include "FBspSurf.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FBspSurf& Value)
    {
        Ar >> Value.Material;
		Ar >> Value.PolyFlags;
		Ar >> Value.pBase;
		Ar >> Value.vNormal;
		Ar >> Value.vTextureU;
		Ar >> Value.vTextureV;
		Ar >> Value.iBrushPoly;
		Ar >> Value.Actor;
		Ar >> Value.Plane;
		Ar >> Value.LightMapScale;
		Ar >> Value.iLightmassIndex;

        return Ar;
    }
}